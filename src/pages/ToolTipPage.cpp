/*
 * Haiku Gallery - tooltips (BView::SetToolTip) page.
 */
#include "ToolTipPage.h"

#include <Button.h>
#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <Slider.h>
#include <StringView.h>
#include <TextControl.h>

#include "Messages.h"


ToolTipPage::ToolTipPage()
	:
	GalleryPage("Tooltips"),
	fButton(NULL),
	fText(NULL),
	fEnabled(NULL)
{
}


const char*
ToolTipPage::Title() const
{
	return "Tooltips";
}


const char*
ToolTipPage::Description() const
{
	return "Any BView can show a tooltip: call SetToolTip() with a string, "
		"or with NULL to remove it. Tooltips appear after the mouse rests "
		"on the view for a moment. For custom content, pass a BToolTip "
		"subclass, or override GetToolTipAt() to change the text depending "
		"on where the mouse is.";
}


const char*
ToolTipPage::SourceSnippet() const
{
	return
"#include <Button.h>\n"
"\n"
"BButton* save = new BButton(\"save\", \"Save\", new BMessage(MSG_SAVE));\n"
"save->SetToolTip(\"Save the document (Alt+S)\");\n"
"\n"
"// Remove it again:\n"
"save->SetToolTip((const char*)NULL);\n";
}


const char*
ToolTipPage::BookClass() const
{
	return "BView";
}


BView*
ToolTipPage::CreateSample()
{
	fButton = new BButton("button", "Hover over me", NULL);
	BStringView* label = new BStringView("label", "Labels can have tips too");
	label->SetToolTip("This tip belongs to a BStringView");
	BSlider* slider = new BSlider("slider", "Slider", NULL, 0, 10,
		B_HORIZONTAL);
	slider->SetToolTip("Sliders, check boxes, lists: any BView");

	BView* view = BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fButton)
		.Add(label)
		.Add(slider)
		.View();
	return view;
}


BView*
ToolTipPage::CreateOptions()
{
	fText = new BTextControl("text", "Tip text:",
		"Buttons are BViews, so they can have tooltips", NULL);
	fText->SetModificationMessage(new BMessage(MSG_TT_TEXT));
	fEnabled = new BCheckBox("enabled", "Show tooltip on the button",
		new BMessage(MSG_TT_ENABLED));
	fEnabled->SetValue(B_CONTROL_ON);
	_Apply();

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fText)
		.Add(fEnabled)
		.View();
}


void
ToolTipPage::_Apply()
{
	if (fEnabled->Value() == B_CONTROL_ON)
		fButton->SetToolTip(fText->Text());
	else
		fButton->SetToolTip((const char*)NULL);
}


bool
ToolTipPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_TT_TEXT:
			_Apply();
			if (fEnabled->Value() == B_CONTROL_ON)
				LogEvent("SetToolTip(\"%s\")", fText->Text());
			return true;

		case MSG_TT_ENABLED:
			_Apply();
			LogEvent("%s", fEnabled->Value() == B_CONTROL_ON
				? "Tooltip set" : "SetToolTip(NULL)");
			return true;
	}
	return GalleryPage::HandleMessage(message);
}
