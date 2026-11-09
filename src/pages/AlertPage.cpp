/*
 * Haiku Gallery - BAlert page.
 */
#include "AlertPage.h"

#include <Alert.h>
#include <Button.h>
#include <Invoker.h>
#include <LayoutBuilder.h>
#include <Messenger.h>
#include <OptionPopUp.h>
#include <TextControl.h>
#include <Window.h>

#include "Messages.h"


static const char* kButtonLabels[] = { "Cancel", "Don't save", "Save" };


AlertPage::AlertPage()
	:
	GalleryPage("BAlert"),
	fType(NULL),
	fButtons(NULL),
	fText(NULL)
{
}


const char*
AlertPage::Title() const
{
	return "BAlert";
}


const char*
AlertPage::Description() const
{
	return "BAlert is a small modal window with an icon, a message and up "
		"to three buttons. Go() without arguments blocks until a button is "
		"pressed and returns its index, which must not be done from a "
		"window's own thread. Go(BInvoker*) returns at once and later "
		"sends the invoker's message with the button index in \"which\". "
		"The alert deletes itself.";
}


const char*
AlertPage::SourceSnippet() const
{
	return
"#include <Alert.h>\n"
"\n"
"BAlert* alert = new BAlert(\"Save changes\",\n"
"\t\"Save changes to the document before closing?\",\n"
"\t\"Cancel\", \"Don't save\", \"Save\",\n"
"\tB_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_WARNING_ALERT);\n"
"alert->SetShortcut(0, B_ESCAPE);\n"
"\n"
"// Asynchronous: the window keeps running.\n"
"alert->Go(new BInvoker(new BMessage(MSG_ALERT_DONE), this));\n"
"\n"
"// In MessageReceived():\n"
"case MSG_ALERT_DONE:\n"
"{\n"
"\tint32 which = message->GetInt32(\"which\", -1);\n"
"\tbreak;\n"
"}\n";
}


BView*
AlertPage::CreateSample()
{
	return BLayoutBuilder::Group<>(B_HORIZONTAL)
		.Add(new BButton("show", "Show alert" B_UTF8_ELLIPSIS,
			new BMessage(MSG_AL_SHOW)))
		.AddGlue()
		.View();
}


BView*
AlertPage::CreateOptions()
{
	fType = new BOptionPopUp("type", "Type:", new BMessage(MSG_AL_TYPE));
	fType->AddOption("Info", B_INFO_ALERT);
	fType->AddOption("Idea", B_IDEA_ALERT);
	fType->AddOption("Warning", B_WARNING_ALERT);
	fType->AddOption("Stop", B_STOP_ALERT);
	fType->AddOption("Empty (no icon)", B_EMPTY_ALERT);
	fType->SetValue(B_WARNING_ALERT);

	fButtons = new BOptionPopUp("buttons", "Buttons:",
		new BMessage(MSG_AL_BUTTONS));
	fButtons->AddOption("1", 1);
	fButtons->AddOption("2", 2);
	fButtons->AddOption("3", 3);
	fButtons->SetValue(3);

	fText = new BTextControl("text", "Text:",
		"Save changes to the document before closing?", NULL);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fType)
		.Add(fButtons)
		.Add(fText)
		.View();
}


bool
AlertPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_AL_SHOW:
		{
			int32 count = fButtons->Value();
			// With one button it is the "Save" one, with two "Cancel"
			// and "Save"; the rightmost button is the default.
			const char* b1 = count == 1 ? kButtonLabels[2] : kButtonLabels[0];
			const char* b2 = count == 2 ? kButtonLabels[2]
				: count == 3 ? kButtonLabels[1] : NULL;
			const char* b3 = count == 3 ? kButtonLabels[2] : NULL;

			BAlert* alert = new BAlert("Haiku Gallery", fText->Text(), b1, b2,
				b3, B_WIDTH_AS_USUAL, B_OFFSET_SPACING,
				(alert_type)fType->Value());
			if (count > 1)
				alert->SetShortcut(0, B_ESCAPE);
			alert->Go(new BInvoker(new BMessage(MSG_AL_RESULT),
				BMessenger(Window())));
			LogEvent("Go(BInvoker*) called; waiting for a button");
			return true;
		}

		case MSG_AL_RESULT:
		{
			int32 which;
			if (message->FindInt32("which", &which) == B_OK)
				LogEvent("Alert closed with button %" B_PRId32, which);
			return true;
		}

		case MSG_AL_TYPE:
		case MSG_AL_BUTTONS:
			LogEvent("Options changed; press \"Show alert\"");
			return true;
	}
	return GalleryPage::HandleMessage(message);
}
