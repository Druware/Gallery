/*
 * Haiku Gallery - BRadioButton page.
 */
#include "RadioButtonPage.h"

#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <RadioButton.h>

#include "Messages.h"


static const char* kSizes[] = { "Small", "Medium", "Large" };


RadioButtonPage::RadioButtonPage()
	:
	GalleryPage("BRadioButton"),
	fEnabled(NULL)
{
	for (int32 i = 0; i < kChoiceCount; i++)
		fChoices[i] = NULL;
}


const char*
RadioButtonPage::Title() const
{
	return "BRadioButton";
}


const char*
RadioButtonPage::Description() const
{
	return "BRadioButton lets the user pick exactly one option from a set. "
		"Radio buttons that share the same parent view form a group: "
		"turning one on turns the others off automatically. Put each set "
		"in its own view (for example a BBox or a BGroupView) to keep "
		"groups apart.";
}


const char*
RadioButtonPage::SourceSnippet() const
{
	return
"#include <RadioButton.h>\n"
"\n"
"BMessage* message = new BMessage(MSG_SIZE);\n"
"message->AddInt32(\"index\", 0);\n"
"BRadioButton* small = new BRadioButton(\"small\", \"Small\", message);\n"
"small->SetValue(B_CONTROL_ON);\n"
"\n"
"// Buttons added to the same parent view are mutually exclusive.\n"
"BLayoutBuilder::Group<>(B_VERTICAL)\n"
"\t.Add(small)\n"
"\t.Add(medium)\n"
"\t.Add(large);\n";
}


BView*
RadioButtonPage::CreateSample()
{
	BGroupLayout* layout;
	BView* view = BLayoutBuilder::Group<>(B_VERTICAL, B_USE_SMALL_SPACING)
		.GetLayout(&layout)
		.View();

	for (int32 i = 0; i < kChoiceCount; i++) {
		BMessage* message = new BMessage(MSG_RB_CHOSEN);
		message->AddInt32("index", i);
		fChoices[i] = new BRadioButton(kSizes[i], kSizes[i], message);
		layout->AddView(fChoices[i]);
	}
	fChoices[1]->SetValue(B_CONTROL_ON);
	return view;
}


BView*
RadioButtonPage::CreateOptions()
{
	fEnabled = new BCheckBox("enabled", "Enabled",
		new BMessage(MSG_RB_ENABLED));
	fEnabled->SetValue(B_CONTROL_ON);
	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fEnabled)
		.View();
}


bool
RadioButtonPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_RB_CHOSEN:
		{
			int32 index;
			if (message->FindInt32("index", &index) == B_OK
				&& index >= 0 && index < kChoiceCount) {
				LogEvent("Selected \"%s\" (index %" B_PRId32 ")",
					kSizes[index], index);
			}
			return true;
		}

		case MSG_RB_ENABLED:
		{
			bool enabled = fEnabled->Value() == B_CONTROL_ON;
			for (int32 i = 0; i < kChoiceCount; i++)
				fChoices[i]->SetEnabled(enabled);
			LogEvent("SetEnabled(%s)", enabled ? "true" : "false");
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
