/*
 * Haiku Gallery - BTextControl page.
 */
#include "TextControlPage.h"

#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <TextControl.h>
#include <TextView.h>

#include "Messages.h"


TextControlPage::TextControlPage()
	:
	GalleryPage("BTextControl"),
	fName(NULL),
	fPassword(NULL),
	fEnabled(NULL),
	fInvalid(NULL),
	fHideTyping(NULL)
{
}


const char*
TextControlPage::Title() const
{
	return "BTextControl";
}


const char*
TextControlPage::Description() const
{
	return "BTextControl is a labelled, single-line text field. It sends "
		"its message when the user presses Enter or the field loses focus "
		"after a change, and its modification message after every "
		"keystroke. In a grid layout, AddTextControl() puts the label and "
		"the field in separate columns so several fields line up.";
}


const char*
TextControlPage::SourceSnippet() const
{
	return
"#include <TextControl.h>\n"
"\n"
"BTextControl* name = new BTextControl(\"name\", \"Name:\", \"\",\n"
"\tnew BMessage(MSG_NAME_ENTERED));\n"
"name->SetModificationMessage(new BMessage(MSG_NAME_TYPED));\n"
"\n"
"BTextControl* password = new BTextControl(\"pw\", \"Password:\", \"\",\n"
"\tNULL);\n"
"password->TextView()->HideTyping(true);\n"
"\n"
"// Labels in column 0, fields in column 1:\n"
"BLayoutBuilder::Grid<>(this)\n"
"\t.AddTextControl(name, 0, 0)\n"
"\t.AddTextControl(password, 0, 1);\n"
"\n"
"name->MarkAsInvalid(strlen(name->Text()) == 0);\n";
}


BView*
TextControlPage::CreateSample()
{
	fName = new BTextControl("name", "Name:", "", new BMessage(MSG_TC_INVOKED));
	fName->SetModificationMessage(new BMessage(MSG_TC_MODIFIED));
	fPassword = new BTextControl("password", "Password:", "", NULL);
	fPassword->TextView()->HideTyping(true);

	return BLayoutBuilder::Grid<>()
		.AddTextControl(fName, 0, 0)
		.AddTextControl(fPassword, 0, 1)
		.View();
}


BView*
TextControlPage::CreateOptions()
{
	fEnabled = new BCheckBox("enabled", "Enabled",
		new BMessage(MSG_TC_ENABLED));
	fEnabled->SetValue(B_CONTROL_ON);
	fInvalid = new BCheckBox("invalid", "Mark name as invalid",
		new BMessage(MSG_TC_INVALID));
	fHideTyping = new BCheckBox("hideTyping", "Hide password typing",
		new BMessage(MSG_TC_PASSWORD));
	fHideTyping->SetValue(B_CONTROL_ON);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fEnabled)
		.Add(fInvalid)
		.Add(fHideTyping)
		.View();
}


bool
TextControlPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_TC_MODIFIED:
			LogEvent("Modified: \"%s\" (%" B_PRId32 " bytes)", fName->Text(),
				fName->TextLength());
			return true;

		case MSG_TC_INVOKED:
			LogEvent("Invoked (Enter or focus change): \"%s\"",
				fName->Text());
			return true;

		case MSG_TC_ENABLED:
		{
			bool enabled = fEnabled->Value() == B_CONTROL_ON;
			fName->SetEnabled(enabled);
			fPassword->SetEnabled(enabled);
			LogEvent("SetEnabled(%s)", enabled ? "true" : "false");
			return true;
		}

		case MSG_TC_INVALID:
		{
			bool invalid = fInvalid->Value() == B_CONTROL_ON;
			fName->MarkAsInvalid(invalid);
			LogEvent("MarkAsInvalid(%s)", invalid ? "true" : "false");
			return true;
		}

		case MSG_TC_PASSWORD:
		{
			bool hide = fHideTyping->Value() == B_CONTROL_ON;
			fPassword->TextView()->HideTyping(hide);
			LogEvent("TextView()->HideTyping(%s)", hide ? "true" : "false");
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
