/*
 * Haiku Gallery - BMenuBar, BMenu and BMenuItem page.
 */
#include "MenuBarPage.h"

#include <string.h>

#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <Menu.h>
#include <MenuBar.h>
#include <MenuItem.h>
#include <StringView.h>

#include "Messages.h"


static BMenuItem*
MakeItem(const char* label)
{
	BMessage* message = new BMessage(MSG_MB_ITEM);
	message->AddString("label", label);
	return new BMenuItem(label, message);
}


MenuBarPage::MenuBarPage()
	:
	GalleryPage("BMenuBar"),
	fEditMenu(NULL),
	fEditEnabled(NULL)
{
}


const char*
MenuBarPage::Title() const
{
	return "BMenuBar";
}


const char*
MenuBarPage::Description() const
{
	return "BMenuBar is the horizontal bar of menus at the top of a "
		"window; each BMenu holds BMenuItem objects, separators and "
		"submenus. An item sends its message when chosen. A menu in radio "
		"mode keeps exactly one item marked, and any item can show a check "
		"mark with SetMarked(). The first BMenuBar added to a window "
		"becomes its key menu bar, opened with Alt/Command+Escape.";
}


const char*
MenuBarPage::SourceSnippet() const
{
	return
"#include <LayoutBuilder.h>\n"
"#include <MenuBar.h>\n"
"\n"
"BMenuBar* menuBar = new BMenuBar(\"menuBar\");\n"
"BLayoutBuilder::Menu<>(menuBar)\n"
"\t.AddMenu(\"File\")\n"
"\t\t.AddItem(\"New\", MSG_NEW, 'N')\n"
"\t\t.AddItem(\"Open\" B_UTF8_ELLIPSIS, MSG_OPEN, 'O')\n"
"\t\t.AddSeparator()\n"
"\t\t.AddItem(\"Quit\", B_QUIT_REQUESTED, 'Q')\n"
"\t.End()\n"
"\t.AddMenu(\"Edit\")\n"
"\t\t.AddItem(\"Copy\", B_COPY, 'C')\n"
"\t\t.AddItem(\"Paste\", B_PASTE, 'V')\n"
"\t.End();\n"
"\n"
"BLayoutBuilder::Group<>(window, B_VERTICAL, 0)\n"
"\t.Add(menuBar)\n"
"\t.Add(content);\n"
"\n"
"// Radio menu: exactly one item is marked\n"
"viewMenu->SetRadioMode(true);\n";
}


BView*
MenuBarPage::CreateSample()
{
	// No shortcuts here: they would be registered with the main window
	// and clash with the real menu bar.
	BMenuBar* menuBar = new BMenuBar("sampleMenuBar");

	BMenu* fileMenu = new BMenu("File");
	fileMenu->AddItem(MakeItem("New"));
	fileMenu->AddItem(MakeItem("Open" B_UTF8_ELLIPSIS));
	BMenu* recent = new BMenu("Open recent");
	recent->AddItem(MakeItem("Notes.txt"));
	recent->AddItem(MakeItem("Budget.ods"));
	fileMenu->AddItem(recent);
	fileMenu->AddSeparatorItem();
	fileMenu->AddItem(MakeItem("Close"));
	menuBar->AddItem(fileMenu);

	fEditMenu = new BMenu("Edit");
	fEditMenu->AddItem(MakeItem("Cut"));
	fEditMenu->AddItem(MakeItem("Copy"));
	fEditMenu->AddItem(MakeItem("Paste"));
	BMenuItem* disabled = MakeItem("Undo (disabled)");
	disabled->SetEnabled(false);
	fEditMenu->AddItem(disabled);
	menuBar->AddItem(fEditMenu);

	BMenu* viewMenu = new BMenu("View");
	viewMenu->SetRadioMode(true);
	viewMenu->AddItem(MakeItem("Icons"));
	viewMenu->AddItem(MakeItem("List"));
	viewMenu->AddItem(MakeItem("Details"));
	viewMenu->ItemAt(1)->SetMarked(true);
	menuBar->AddItem(viewMenu);

	BMenu* optionsMenu = new BMenu("Options");
	BMenuItem* hidden = MakeItem("Show hidden files");
	optionsMenu->AddItem(hidden);
	menuBar->AddItem(optionsMenu);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(menuBar)
		.Add(new BStringView("hint", "Open the menus above and pick items."))
		.View();
}


BView*
MenuBarPage::CreateOptions()
{
	fEditEnabled = new BCheckBox("editEnabled", "Edit menu enabled",
		new BMessage(MSG_MB_EDIT_ENABLED));
	fEditEnabled->SetValue(B_CONTROL_ON);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fEditEnabled)
		.View();
}


bool
MenuBarPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_MB_ITEM:
		{
			const char* label = "";
			message->FindString("label", &label);

			// "Show hidden files" acts as a check box item.
			BMenuItem* source = NULL;
			if (message->FindPointer("source", (void**)&source) == B_OK
				&& source != NULL && source->Menu() != NULL
				&& !source->Menu()->IsRadioMode()
				&& strcmp(source->Label(), "Show hidden files") == 0) {
				source->SetMarked(!source->IsMarked());
				LogEvent("%s: %s", label, source->IsMarked() ? "on" : "off");
				return true;
			}
			LogEvent("Menu item chosen: %s", label);
			return true;
		}

		case MSG_MB_EDIT_ENABLED:
		{
			bool enabled = fEditEnabled->Value() == B_CONTROL_ON;
			fEditMenu->SetEnabled(enabled);
			LogEvent("Edit menu SetEnabled(%s)", enabled ? "true" : "false");
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
