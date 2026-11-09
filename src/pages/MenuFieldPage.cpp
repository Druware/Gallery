/*
 * Haiku Gallery - BMenuField page.
 */
#include "MenuFieldPage.h"

#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <MenuField.h>
#include <MenuItem.h>
#include <PopUpMenu.h>
#include <TextControl.h>

#include "Messages.h"


static const char* kPlanets[] = {
	"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus",
	"Neptune"
};


MenuFieldPage::MenuFieldPage()
	:
	GalleryPage("BMenuField"),
	fField(NULL),
	fEnabled(NULL),
	fLabel(NULL)
{
}


const char*
MenuFieldPage::Title() const
{
	return "BMenuField";
}


const char*
MenuFieldPage::Description() const
{
	return "BMenuField is a label plus a pop-up menu that shows the current "
		"choice, Haiku's equivalent of a drop-down list. With a "
		"BPopUpMenu in radio mode and label-from-marked enabled (the "
		"defaults), the field always displays the marked item. Each item "
		"sends its own message; add a field to it to tell items apart.";
}


const char*
MenuFieldPage::SourceSnippet() const
{
	return
"#include <MenuField.h>\n"
"#include <MenuItem.h>\n"
"#include <PopUpMenu.h>\n"
"\n"
"BPopUpMenu* menu = new BPopUpMenu(\"planet\");  // radio, label from mark\n"
"for (int32 i = 0; i < count; i++) {\n"
"\tBMessage* message = new BMessage(MSG_PLANET);\n"
"\tmessage->AddString(\"label\", kPlanets[i]);\n"
"\tmenu->AddItem(new BMenuItem(kPlanets[i], message));\n"
"}\n"
"menu->ItemAt(2)->SetMarked(true);\n"
"\n"
"BMenuField* field = new BMenuField(\"planet\", \"Planet:\", menu);\n"
"\n"
"// In a grid, label and menu go in separate columns:\n"
"BLayoutBuilder::Grid<>(this)\n"
"\t.AddMenuField(field, 0, 0);\n";
}


BView*
MenuFieldPage::CreateSample()
{
	BPopUpMenu* menu = new BPopUpMenu("planet");
	for (size_t i = 0; i < sizeof(kPlanets) / sizeof(kPlanets[0]); i++) {
		BMessage* message = new BMessage(MSG_MF_SELECTED);
		message->AddString("label", kPlanets[i]);
		menu->AddItem(new BMenuItem(kPlanets[i], message));
	}
	menu->ItemAt(2)->SetMarked(true);

	fField = new BMenuField("planet", "Planet:", menu);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.AddGrid()
			.AddMenuField(fField, 0, 0)
		.End()
		.View();
}


BView*
MenuFieldPage::CreateOptions()
{
	fEnabled = new BCheckBox("enabled", "Enabled",
		new BMessage(MSG_MF_ENABLED));
	fEnabled->SetValue(B_CONTROL_ON);
	fLabel = new BTextControl("label", "Label:", "Planet:", NULL);
	fLabel->SetModificationMessage(new BMessage(MSG_MF_LABEL));

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fEnabled)
		.Add(fLabel)
		.View();
}


bool
MenuFieldPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_MF_SELECTED:
		{
			const char* label = "";
			message->FindString("label", &label);
			LogEvent("Selected: %s", label);
			return true;
		}

		case MSG_MF_ENABLED:
		{
			bool enabled = fEnabled->Value() == B_CONTROL_ON;
			fField->SetEnabled(enabled);
			LogEvent("SetEnabled(%s)", enabled ? "true" : "false");
			return true;
		}

		case MSG_MF_LABEL:
			fField->SetLabel(fLabel->Text());
			LogEvent("SetLabel(\"%s\")", fLabel->Text());
			return true;
	}
	return GalleryPage::HandleMessage(message);
}
