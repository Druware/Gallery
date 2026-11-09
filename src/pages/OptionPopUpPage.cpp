/*
 * Haiku Gallery - BOptionPopUp page.
 */
#include "OptionPopUpPage.h"

#include <Button.h>
#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <OptionPopUp.h>
#include <String.h>

#include "Messages.h"


OptionPopUpPage::OptionPopUpPage()
	:
	GalleryPage("BOptionPopUp"),
	fPopUp(NULL),
	fEnabled(NULL),
	fAdded(0)
{
}


const char*
OptionPopUpPage::Title() const
{
	return "BOptionPopUp";
}


const char*
OptionPopUpPage::Description() const
{
	return "BOptionPopUp is a BControl that wraps a BMenuField: each option "
		"is a name paired with an int32 value, and Value() returns the "
		"value of the chosen option. Compared with building a BMenuField "
		"by hand it needs less code and behaves like any other control: "
		"one message, SetValue(), SetEnabled().";
}


const char*
OptionPopUpPage::SourceSnippet() const
{
	return
"#include <OptionPopUp.h>\n"
"\n"
"BOptionPopUp* speed = new BOptionPopUp(\"speed\", \"Speed:\",\n"
"\tnew BMessage(MSG_SPEED));\n"
"speed->AddOption(\"Slow\", 1);\n"
"speed->AddOption(\"Normal\", 2);\n"
"speed->AddOption(\"Fast\", 3);\n"
"speed->SetValue(2);\n"
"\n"
"// In MessageReceived():\n"
"case MSG_SPEED:\n"
"{\n"
"\tconst char* name;\n"
"\tint32 value;\n"
"\tspeed->SelectedOption(&name, &value);\n"
"\tbreak;\n"
"}\n";
}


BView*
OptionPopUpPage::CreateSample()
{
	fPopUp = new BOptionPopUp("speed", "Speed:",
		new BMessage(MSG_OP_CHANGED));
	fPopUp->AddOption("Slow", 1);
	fPopUp->AddOption("Normal", 2);
	fPopUp->AddOption("Fast", 3);
	fPopUp->SetValue(2);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fPopUp)
		.View();
}


BView*
OptionPopUpPage::CreateOptions()
{
	fEnabled = new BCheckBox("enabled", "Enabled",
		new BMessage(MSG_OP_ENABLED));
	fEnabled->SetValue(B_CONTROL_ON);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fEnabled)
		.Add(new BButton("add", "Add option", new BMessage(MSG_OP_ADD)))
		.View();
}


bool
OptionPopUpPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_OP_CHANGED:
		{
			const char* name = NULL;
			int32 value = 0;
			if (fPopUp->SelectedOption(&name, &value) >= 0) {
				LogEvent("Selected \"%s\", Value() = %" B_PRId32, name,
					value);
			}
			return true;
		}

		case MSG_OP_ENABLED:
		{
			bool enabled = fEnabled->Value() == B_CONTROL_ON;
			fPopUp->SetEnabled(enabled);
			LogEvent("SetEnabled(%s)", enabled ? "true" : "false");
			return true;
		}

		case MSG_OP_ADD:
		{
			BString name;
			name.SetToFormat("Custom %" B_PRId32, ++fAdded);
			fPopUp->AddOption(name.String(), 100 + fAdded);
			LogEvent("AddOption(\"%s\", %" B_PRId32 ")", name.String(),
				100 + fAdded);
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
