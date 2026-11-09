/*
 * Haiku Gallery - BSeparatorView page.
 */
#include "SeparatorViewPage.h"

#include <LayoutBuilder.h>
#include <OptionPopUp.h>
#include <SeparatorView.h>
#include <StringView.h>
#include <TextControl.h>

#include "Messages.h"


SeparatorViewPage::SeparatorViewPage()
	:
	GalleryPage("BSeparatorView"),
	fSeparator(NULL),
	fLabel(NULL),
	fBorder(NULL),
	fAlignment(NULL)
{
}


const char*
SeparatorViewPage::Title() const
{
	return "BSeparatorView";
}


const char*
SeparatorViewPage::Description() const
{
	return "BSeparatorView draws a horizontal or vertical line to divide "
		"parts of a layout, optionally with a label set into the line. It "
		"is lighter than a BBox when you only need a heading between "
		"sections; the home page uses labelled separators for its "
		"category headings.";
}


const char*
SeparatorViewPage::SourceSnippet() const
{
	return
"#include <SeparatorView.h>\n"
"\n"
"BLayoutBuilder::Group<>(this, B_VERTICAL)\n"
"\t.Add(new BSeparatorView(\"General\", B_HORIZONTAL,\n"
"\t\tB_FANCY_BORDER,\n"
"\t\tBAlignment(B_ALIGN_LEFT, B_ALIGN_VERTICAL_CENTER)))\n"
"\t.Add(generalSettings)\n"
"\t.Add(new BSeparatorView(B_HORIZONTAL))   // plain line\n"
"\t.Add(otherSettings);\n";
}


BView*
SeparatorViewPage::CreateSample()
{
	fSeparator = new BSeparatorView("separator", "Section heading",
		B_HORIZONTAL, B_FANCY_BORDER,
		BAlignment(B_ALIGN_LEFT, B_ALIGN_VERTICAL_CENTER));

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fSeparator)
		.Add(new BStringView("above", "Content of the section."))
		.AddGroup(B_HORIZONTAL)
			.Add(new BStringView("left", "Left"))
			.Add(new BSeparatorView(B_VERTICAL))
			.Add(new BStringView("right", "Right of a vertical separator"))
			.AddGlue()
		.End()
		.Add(new BSeparatorView(B_HORIZONTAL))
		.Add(new BStringView("below", "Below a plain separator."))
		.View();
}


BView*
SeparatorViewPage::CreateOptions()
{
	fLabel = new BTextControl("label", "Label:", "Section heading", NULL);
	fLabel->SetModificationMessage(new BMessage(MSG_SE_LABEL));

	fBorder = new BOptionPopUp("border", "Border:",
		new BMessage(MSG_SE_BORDER));
	fBorder->AddOption("Fancy", B_FANCY_BORDER);
	fBorder->AddOption("Plain", B_PLAIN_BORDER);
	fBorder->AddOption("None", B_NO_BORDER);
	fBorder->SetValue(B_FANCY_BORDER);

	fAlignment = new BOptionPopUp("alignment", "Label alignment:",
		new BMessage(MSG_SE_ALIGN));
	fAlignment->AddOption("Left", B_ALIGN_LEFT);
	fAlignment->AddOption("Center", B_ALIGN_HORIZONTAL_CENTER);
	fAlignment->AddOption("Right", B_ALIGN_RIGHT);
	fAlignment->SetValue(B_ALIGN_LEFT);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fLabel)
		.Add(fBorder)
		.Add(fAlignment)
		.View();
}


bool
SeparatorViewPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_SE_LABEL:
			fSeparator->SetLabel(fLabel->Text());
			LogEvent("SetLabel(\"%s\")", fLabel->Text());
			return true;

		case MSG_SE_BORDER:
			fSeparator->SetBorderStyle((border_style)fBorder->Value());
			LogEvent("SetBorderStyle(%" B_PRId32 ")", fBorder->Value());
			return true;

		case MSG_SE_ALIGN:
			fSeparator->SetAlignment(BAlignment(
				(alignment)fAlignment->Value(), B_ALIGN_VERTICAL_CENTER));
			LogEvent("SetAlignment(%" B_PRId32 ")", fAlignment->Value());
			return true;
	}
	return GalleryPage::HandleMessage(message);
}
