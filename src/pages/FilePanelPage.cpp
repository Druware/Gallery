/*
 * Haiku Gallery - BFilePanel page.
 */
#include "FilePanelPage.h"

#include <Button.h>
#include <CheckBox.h>
#include <Entry.h>
#include <FilePanel.h>
#include <LayoutBuilder.h>
#include <Messenger.h>
#include <Path.h>
#include <String.h>
#include <Window.h>

#include "Messages.h"


FilePanelPage::FilePanelPage()
	:
	GalleryPage("BFilePanel"),
	fPanel(NULL),
	fMultiple(NULL),
	fDirectories(NULL)
{
}


FilePanelPage::~FilePanelPage()
{
	delete fPanel;
}


const char*
FilePanelPage::Title() const
{
	return "BFilePanel";
}


const char*
FilePanelPage::Description() const
{
	return "BFilePanel is the standard Open and Save dialog, provided by "
		"Tracker (link with libtracker). It runs in its own window and "
		"reports back asynchronously: an open panel sends the chosen "
		"entry_refs in a \"refs\" field, a save panel sends the target "
		"\"directory\" and \"name\", and closing the panel sends "
		"B_CANCEL.";
}


const char*
FilePanelPage::SourceSnippet() const
{
	return
"#include <FilePanel.h>   // link with libtracker\n"
"\n"
"BMessenger target(this);\n"
"BFilePanel* panel = new BFilePanel(B_OPEN_PANEL, &target, NULL,\n"
"\tB_FILE_NODE, true /* multiple */, new BMessage(MSG_OPENED));\n"
"panel->Show();\n"
"\n"
"// In MessageReceived():\n"
"case MSG_OPENED:\n"
"{\n"
"\tentry_ref ref;\n"
"\tfor (int32 i = 0;\n"
"\t\t\tmessage->FindRef(\"refs\", i, &ref) == B_OK; i++)\n"
"\t\tOpenFile(ref);\n"
"\tbreak;\n"
"}\n"
"\n"
"// Keep the panel around and delete it when you are done.\n";
}


BView*
FilePanelPage::CreateSample()
{
	return BLayoutBuilder::Group<>(B_HORIZONTAL)
		.Add(new BButton("open", "Open" B_UTF8_ELLIPSIS,
			new BMessage(MSG_FP_SHOW_OPEN)))
		.Add(new BButton("save", "Save as" B_UTF8_ELLIPSIS,
			new BMessage(MSG_FP_SHOW_SAVE)))
		.AddGlue()
		.View();
}


BView*
FilePanelPage::CreateOptions()
{
	fMultiple = new BCheckBox("multiple", "Allow multiple selection", NULL);
	fMultiple->SetValue(B_CONTROL_ON);
	fDirectories = new BCheckBox("directories", "Open folders instead of "
		"files", NULL);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fMultiple)
		.Add(fDirectories)
		.View();
}


void
FilePanelPage::_ShowPanel(bool save)
{
	// A panel's mode and node flavors are fixed at construction, so a
	// fresh panel is made each time with the current options.
	delete fPanel;

	BMessenger target(Window());
	uint32 flavors = fDirectories->Value() == B_CONTROL_ON
		? B_DIRECTORY_NODE : B_FILE_NODE;
	BMessage message(save ? MSG_FP_SAVED : MSG_FP_OPENED);
	fPanel = new BFilePanel(save ? B_SAVE_PANEL : B_OPEN_PANEL, &target,
		NULL, save ? 0 : flavors, fMultiple->Value() == B_CONTROL_ON,
		&message);
	fPanel->Show();
	LogEvent("Showing %s panel", save ? "save" : "open");
}


bool
FilePanelPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_FP_SHOW_OPEN:
			_ShowPanel(false);
			return true;

		case MSG_FP_SHOW_SAVE:
			_ShowPanel(true);
			return true;

		case MSG_FP_OPENED:
		{
			entry_ref ref;
			int32 count = 0;
			BString first;
			while (message->FindRef("refs", count, &ref) == B_OK) {
				if (count == 0)
					first = BPath(&ref).Path();
				count++;
			}
			if (count == 1)
				LogEvent("Opened %s", first.String());
			else
				LogEvent("Opened %" B_PRId32 " items, first: %s", count,
					first.String());
			return true;
		}

		case MSG_FP_SAVED:
		{
			entry_ref directory;
			const char* name;
			if (message->FindRef("directory", &directory) == B_OK
				&& message->FindString("name", &name) == B_OK) {
				BPath path(&directory);
				path.Append(name);
				LogEvent("Save requested: %s", path.Path());
			}
			return true;
		}

		case B_CANCEL:
			// Sent when a file panel closes, whether or not a file was
			// chosen. Only this page opens file panels.
			if (fPanel != NULL) {
				LogEvent("Panel closed (B_CANCEL)");
				return true;
			}
			return false;
	}
	return GalleryPage::HandleMessage(message);
}
