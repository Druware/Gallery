/*
 * Haiku Gallery - BCheckBox page.
 */
#include "CheckBoxPage.h"

#include <CheckBox.h>
#include <LayoutBuilder.h>

#include "Messages.h"


static const char* kToppings[] = { "Cheese", "Mushrooms", "Olives" };


CheckBoxPage::CheckBoxPage()
	:
	GalleryPage("BCheckBox"),
	fAll(NULL),
	fEnabled(NULL)
{
	for (int32 i = 0; i < kItemCount; i++)
		fItems[i] = NULL;
}


const char*
CheckBoxPage::Title() const
{
	return "BCheckBox";
}


const char*
CheckBoxPage::Description() const
{
	return "BCheckBox is an on/off control with a label. Its Value() is "
		"B_CONTROL_OFF or B_CONTROL_ON, and you can also set "
		"B_CONTROL_PARTIALLY_ON to show a mixed state, as the \"All "
		"toppings\" box does here when only some toppings are chosen.";
}


const char*
CheckBoxPage::SourceSnippet() const
{
	return
"#include <CheckBox.h>\n"
"\n"
"BCheckBox* all = new BCheckBox(\"all\", \"All toppings\",\n"
"\tnew BMessage(MSG_ALL));\n"
"BCheckBox* cheese = new BCheckBox(\"cheese\", \"Cheese\",\n"
"\tnew BMessage(MSG_ITEM));\n"
"\n"
"// Show a mixed state when only some items are checked:\n"
"all->SetValue(someChecked ? B_CONTROL_PARTIALLY_ON\n"
"\t: allChecked ? B_CONTROL_ON : B_CONTROL_OFF);\n";
}


BView*
CheckBoxPage::CreateSample()
{
	fAll = new BCheckBox("all", "All toppings", new BMessage(MSG_CB_ALL));

	BGroupLayout* items;
	BView* view = BLayoutBuilder::Group<>(B_VERTICAL, B_USE_SMALL_SPACING)
		.Add(fAll)
		.AddGroup(B_VERTICAL, B_USE_SMALL_SPACING)
			.GetLayout(&items)
			.SetInsets(B_USE_ITEM_INSETS, 0, 0, 0)
		.End()
		.View();

	for (int32 i = 0; i < kItemCount; i++) {
		fItems[i] = new BCheckBox(kToppings[i], kToppings[i],
			new BMessage(MSG_CB_ITEM));
		items->AddView(fItems[i]);
	}
	fItems[0]->SetValue(B_CONTROL_ON);
	_UpdateAll();
	return view;
}


BView*
CheckBoxPage::CreateOptions()
{
	fEnabled = new BCheckBox("enabled", "Enabled",
		new BMessage(MSG_CB_ENABLED));
	fEnabled->SetValue(B_CONTROL_ON);
	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fEnabled)
		.View();
}


void
CheckBoxPage::_UpdateAll()
{
	int32 checked = 0;
	for (int32 i = 0; i < kItemCount; i++) {
		if (fItems[i]->Value() == B_CONTROL_ON)
			checked++;
	}
	if (checked == 0)
		fAll->SetValue(B_CONTROL_OFF);
	else if (checked == kItemCount)
		fAll->SetValue(B_CONTROL_ON);
	else
		fAll->SetValue(B_CONTROL_PARTIALLY_ON);
}


bool
CheckBoxPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_CB_ALL:
		{
			// Clicking a partially-on box turns it on.
			int32 value = fAll->Value() == B_CONTROL_OFF
				? B_CONTROL_OFF : B_CONTROL_ON;
			fAll->SetValue(value);
			for (int32 i = 0; i < kItemCount; i++)
				fItems[i]->SetValue(value);
			LogEvent("All toppings: %s", value == B_CONTROL_ON ? "on" : "off");
			return true;
		}

		case MSG_CB_ITEM:
		{
			BControl* source = NULL;
			message->FindPointer("source", (void**)&source);
			_UpdateAll();
			if (source != NULL) {
				LogEvent("%s: %s", source->Label(),
					source->Value() == B_CONTROL_ON ? "on" : "off");
			}
			return true;
		}

		case MSG_CB_ENABLED:
		{
			bool enabled = fEnabled->Value() == B_CONTROL_ON;
			fAll->SetEnabled(enabled);
			for (int32 i = 0; i < kItemCount; i++)
				fItems[i]->SetEnabled(enabled);
			LogEvent("SetEnabled(%s)", enabled ? "true" : "false");
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
