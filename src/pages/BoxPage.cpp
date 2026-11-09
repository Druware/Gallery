/*
 * Haiku Gallery - BBox page.
 */
#include "BoxPage.h"

#include <Box.h>
#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <OptionPopUp.h>
#include <RadioButton.h>
#include <TextControl.h>

#include "Messages.h"


BoxPage::BoxPage()
	:
	GalleryPage("BBox"),
	fBox(NULL),
	fContent(NULL),
	fBorder(NULL),
	fLabel(NULL),
	fViewLabel(NULL)
{
}


const char*
BoxPage::Title() const
{
	return "BBox";
}


const char*
BoxPage::Description() const
{
	return "BBox draws a frame around a group of related controls, with "
		"an optional label in the top border. The label can be text or any "
		"view, commonly a BCheckBox that enables the whole group. Give the "
		"box a single child view with its own layout; the box keeps it "
		"inside the frame.";
}


const char*
BoxPage::SourceSnippet() const
{
	return
"#include <Box.h>\n"
"#include <LayoutBuilder.h>\n"
"\n"
"BBox* box = new BBox(\"network\");\n"
"box->SetLabel(\"Network\");\n"
"box->AddChild(BLayoutBuilder::Group<>(B_VERTICAL)\n"
"\t.SetInsets(B_USE_DEFAULT_SPACING)\n"
"\t.Add(dhcpRadio)\n"
"\t.Add(manualRadio)\n"
"\t.View());\n"
"\n"
"// A check box as the label:\n"
"box->SetLabel(new BCheckBox(\"proxy\", \"Use a proxy\",\n"
"\tnew BMessage(MSG_PROXY)));\n"
"box->SetBorder(B_PLAIN_BORDER);\n";
}


BView*
BoxPage::CreateSample()
{
	fBox = new BBox("box");
	fContent = BLayoutBuilder::Group<>(B_VERTICAL)
		.SetInsets(B_USE_DEFAULT_SPACING)
		.Add(new BRadioButton("dhcp", "Automatic (DHCP)", NULL))
		.Add(new BRadioButton("manual", "Manual", NULL))
		.View();
	fBox->AddChild(fContent);
	fBox->SetLabel("Network");

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fBox)
		.View();
}


BView*
BoxPage::CreateOptions()
{
	fBorder = new BOptionPopUp("border", "Border:",
		new BMessage(MSG_BX_BORDER));
	fBorder->AddOption("Fancy", B_FANCY_BORDER);
	fBorder->AddOption("Plain", B_PLAIN_BORDER);
	fBorder->AddOption("None", B_NO_BORDER);
	fBorder->SetValue(B_FANCY_BORDER);

	fLabel = new BTextControl("label", "Label:", "Network", NULL);
	fLabel->SetModificationMessage(new BMessage(MSG_BX_LABEL));
	fViewLabel = new BCheckBox("viewLabel", "Use a check box as label",
		new BMessage(MSG_BX_VIEW_LABEL));

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fBorder)
		.Add(fLabel)
		.Add(fViewLabel)
		.View();
}


void
BoxPage::_UpdateLabel()
{
	if (fViewLabel->Value() == B_CONTROL_ON) {
		// SetLabel(BView*) takes ownership and deletes the old label.
		BCheckBox* check = new BCheckBox("labelCheck", fLabel->Text(),
			new BMessage(MSG_BX_LABEL_CHECK));
		check->SetValue(B_CONTROL_ON);
		fBox->SetLabel(check);
	} else
		fBox->SetLabel(fLabel->Text());
}


bool
BoxPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_BX_BORDER:
			fBox->SetBorder((border_style)fBorder->Value());
			LogEvent("SetBorder(%" B_PRId32 ")", fBorder->Value());
			return true;

		case MSG_BX_LABEL:
			_UpdateLabel();
			LogEvent("SetLabel(\"%s\")", fLabel->Text());
			return true;

		case MSG_BX_VIEW_LABEL:
			_UpdateLabel();
			LogEvent("%s", fViewLabel->Value() == B_CONTROL_ON
				? "SetLabel(BView*): label is a BCheckBox"
				: "SetLabel(const char*)");
			return true;

		case MSG_BX_LABEL_CHECK:
		{
			BControl* check = NULL;
			message->FindPointer("source", (void**)&check);
			bool enabled = check == NULL || check->Value() == B_CONTROL_ON;
			for (int32 i = 0; i < fContent->CountChildren(); i++) {
				BControl* control = dynamic_cast<BControl*>(
					fContent->ChildAt(i));
				if (control != NULL)
					control->SetEnabled(enabled);
			}
			LogEvent("Label check box: group %s",
				enabled ? "enabled" : "disabled");
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
