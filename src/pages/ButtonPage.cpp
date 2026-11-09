/*
 * Haiku Gallery - BButton page.
 */
#include "ButtonPage.h"

#include <Button.h>
#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <TextControl.h>

#include "Messages.h"


ButtonPage::ButtonPage()
	:
	GalleryPage("BButton"),
	fButton(NULL),
	fToggle(NULL),
	fEnabled(NULL),
	fLabel(NULL),
	fClicks(0)
{
}


const char*
ButtonPage::Title() const
{
	return "BButton";
}


const char*
ButtonPage::Description() const
{
	return "BButton is a push button: clicking it sends its BMessage to "
		"its target, which is the window unless you call SetTarget(). With "
		"SetBehavior(B_TOGGLE_BEHAVIOR) it stays pressed between clicks "
		"and its Value() switches between B_CONTROL_OFF and B_CONTROL_ON.";
}


const char*
ButtonPage::SourceSnippet() const
{
	return
"#include <Button.h>\n"
"#include <LayoutBuilder.h>\n"
"\n"
"const uint32 MSG_CLICKED = 'clck';\n"
"\n"
"BButton* button = new BButton(\"ok\", \"Click me\",\n"
"\tnew BMessage(MSG_CLICKED));\n"
"button->SetToolTip(\"Sends MSG_CLICKED to the window\");\n"
"\n"
"BButton* toggle = new BButton(\"toggle\", \"Toggle\", NULL);\n"
"toggle->SetBehavior(BButton::B_TOGGLE_BEHAVIOR);\n"
"\n"
"BLayoutBuilder::Group<>(this, B_HORIZONTAL)\n"
"\t.Add(button)\n"
"\t.Add(toggle);\n"
"\n"
"// In your window's MessageReceived():\n"
"case MSG_CLICKED:\n"
"\tputs(\"Clicked\");\n"
"\tbreak;\n";
}


BView*
ButtonPage::CreateSample()
{
	fButton = new BButton("button", "Click me",
		new BMessage(MSG_BTN_CLICKED));
	fToggle = new BButton("toggle", "Toggle",
		new BMessage(MSG_BTN_TOGGLED));
	fToggle->SetBehavior(BButton::B_TOGGLE_BEHAVIOR);

	return BLayoutBuilder::Group<>(B_HORIZONTAL)
		.Add(fButton)
		.Add(fToggle)
		.AddGlue()
		.View();
}


BView*
ButtonPage::CreateOptions()
{
	fEnabled = new BCheckBox("enabled", "Enabled",
		new BMessage(MSG_BTN_ENABLED));
	fEnabled->SetValue(B_CONTROL_ON);
	fLabel = new BTextControl("label", "Label:", "Click me", NULL);
	fLabel->SetModificationMessage(new BMessage(MSG_BTN_LABEL));

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fEnabled)
		.Add(fLabel)
		.View();
}


bool
ButtonPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_BTN_CLICKED:
			fClicks++;
			LogEvent("Clicked (%" B_PRId32 " so far)", fClicks);
			return true;

		case MSG_BTN_TOGGLED:
			LogEvent("Toggle value: %s",
				fToggle->Value() == B_CONTROL_ON ? "on" : "off");
			return true;

		case MSG_BTN_ENABLED:
		{
			bool enabled = fEnabled->Value() == B_CONTROL_ON;
			fButton->SetEnabled(enabled);
			fToggle->SetEnabled(enabled);
			LogEvent("SetEnabled(%s)", enabled ? "true" : "false");
			return true;
		}

		case MSG_BTN_LABEL:
			fButton->SetLabel(fLabel->Text());
			LogEvent("SetLabel(\"%s\")", fLabel->Text());
			return true;
	}
	return GalleryPage::HandleMessage(message);
}
