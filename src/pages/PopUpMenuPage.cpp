/*
 * Haiku Gallery - BPopUpMenu page.
 */
#include "PopUpMenuPage.h"

#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <MenuItem.h>
#include <PopUpMenu.h>
#include <Window.h>

#include "Messages.h"


static const char* kColors[] = { "Red", "Green", "Blue" };
static const int32 kColorCount = 3;


// A view that opens a context menu when clicked.
class PopUpArea : public BView {
public:
	PopUpArea()
		:
		BView("popUpArea", B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE),
		fMarked(0),
		fShowDisabled(true)
	{
		SetViewUIColor(B_DOCUMENT_BACKGROUND_COLOR);
		SetExplicitMinSize(BSize(240, 90));
	}

	void SetShowDisabled(bool show)
	{
		fShowDisabled = show;
	}

	virtual void Draw(BRect updateRect)
	{
		BRect bounds = Bounds();
		SetHighUIColor(B_DOCUMENT_TEXT_COLOR);
		StrokeRect(bounds);

		const char* text = "Click or right-click here";
		font_height height;
		GetFontHeight(&height);
		BPoint where((bounds.Width() - StringWidth(text)) / 2,
			(bounds.Height() + height.ascent - height.descent) / 2);
		DrawString(text, where);
	}

	virtual void MouseDown(BPoint where)
	{
		BPopUpMenu* menu = new BPopUpMenu("context", false, false);
		for (int32 i = 0; i < kColorCount; i++) {
			BMenuItem* item = new BMenuItem(kColors[i], NULL);
			item->SetMarked(i == fMarked);
			menu->AddItem(item);
		}
		menu->AddSeparatorItem();
		menu->AddItem(new BMenuItem("Reset", NULL));
		if (fShowDisabled) {
			BMenuItem* disabled = new BMenuItem("Unavailable", NULL);
			disabled->SetEnabled(false);
			menu->AddItem(disabled);
		}

		// Go() without auto-invoke returns the chosen item (or NULL)
		// and leaves handling it to us. keepOpen = true lets a simple
		// click open the menu without holding the button.
		ConvertToScreen(&where);
		BMenuItem* chosen = menu->Go(where, false, true);
		if (chosen != NULL) {
			int32 index = menu->IndexOf(chosen);
			if (index < kColorCount)
				fMarked = index;
			else
				fMarked = 0;
			BMessage message(MSG_PM_PICKED);
			message.AddString("label", chosen->Label());
			Window()->PostMessage(&message);
		}
		delete menu;
	}

private:
	int32	fMarked;
	bool	fShowDisabled;
};


PopUpMenuPage::PopUpMenuPage()
	:
	GalleryPage("BPopUpMenu"),
	fArea(NULL),
	fDisabledItem(NULL)
{
}


const char*
PopUpMenuPage::Title() const
{
	return "BPopUpMenu";
}


const char*
PopUpMenuPage::Description() const
{
	return "BPopUpMenu is a menu that appears on demand, typically as a "
		"context menu under the mouse. Go() shows it and, unless you ask "
		"it to invoke the item itself, returns the chosen BMenuItem so you "
		"can act on it directly. It is also the menu type used inside a "
		"BMenuField.";
}


const char*
PopUpMenuPage::SourceSnippet() const
{
	return
"#include <MenuItem.h>\n"
"#include <PopUpMenu.h>\n"
"\n"
"void\n"
"MyView::MouseDown(BPoint where)\n"
"{\n"
"\tBPopUpMenu* menu = new BPopUpMenu(\"context\", false, false);\n"
"\tmenu->AddItem(new BMenuItem(\"Red\", NULL));\n"
"\tmenu->AddItem(new BMenuItem(\"Green\", NULL));\n"
"\n"
"\tConvertToScreen(&where);\n"
"\tBMenuItem* chosen = menu->Go(where, false, true);\n"
"\tif (chosen != NULL)\n"
"\t\tprintf(\"Picked %s\\n\", chosen->Label());\n"
"\tdelete menu;\n"
"}\n";
}


BView*
PopUpMenuPage::CreateSample()
{
	fArea = new PopUpArea();
	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fArea)
		.View();
}


BView*
PopUpMenuPage::CreateOptions()
{
	fDisabledItem = new BCheckBox("disabledItem", "Include a disabled item",
		new BMessage(MSG_PM_DISABLED_ITEM));
	fDisabledItem->SetValue(B_CONTROL_ON);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fDisabledItem)
		.View();
}


bool
PopUpMenuPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_PM_PICKED:
		{
			const char* label = "";
			message->FindString("label", &label);
			LogEvent("Go() returned \"%s\"", label);
			return true;
		}

		case MSG_PM_DISABLED_ITEM:
		{
			bool show = fDisabledItem->Value() == B_CONTROL_ON;
			fArea->SetShowDisabled(show);
			LogEvent("Disabled item %s", show ? "shown" : "hidden");
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
