/*
 * Haiku Gallery - BStringView page.
 */
#include "StringViewPage.h"

#include <CheckBox.h>
#include <Font.h>
#include <LayoutBuilder.h>
#include <OptionPopUp.h>
#include <StringView.h>
#include <TextControl.h>

#include "Messages.h"


static const char* kInitialText
	= "The quick brown fox jumps over the lazy dog";


StringViewPage::StringViewPage()
	:
	GalleryPage("BStringView"),
	fString(NULL),
	fText(NULL),
	fAlignment(NULL),
	fTruncation(NULL),
	fBold(NULL)
{
}


const char*
StringViewPage::Title() const
{
	return "BStringView";
}


const char*
StringViewPage::Description() const
{
	return "BStringView draws a single line of static, non-editable text. "
		"Use it for labels and short status messages. When the view is "
		"narrower than its text, the text is truncated according to "
		"SetTruncation(); make the window narrower to see it. It sends no "
		"messages.";
}


const char*
StringViewPage::SourceSnippet() const
{
	return
"#include <StringView.h>\n"
"\n"
"BStringView* label = new BStringView(\"status\", \"Ready\");\n"
"label->SetAlignment(B_ALIGN_CENTER);\n"
"label->SetTruncation(B_TRUNCATE_MIDDLE);\n"
"\n"
"BFont font(be_bold_font);\n"
"label->SetFont(&font);\n"
"\n"
"// Let it shrink below its preferred width so truncation can happen:\n"
"label->SetExplicitMinSize(BSize(50, B_SIZE_UNSET));\n"
"label->SetText(\"Copying 12 files\");\n";
}


BView*
StringViewPage::CreateSample()
{
	fString = new BStringView("string", kInitialText);
	fString->SetExplicitMinSize(BSize(50, B_SIZE_UNSET));
	fString->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED, B_SIZE_UNSET));

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fString)
		.View();
}


BView*
StringViewPage::CreateOptions()
{
	fText = new BTextControl("text", "Text:", kInitialText, NULL);
	fText->SetModificationMessage(new BMessage(MSG_SV_TEXT));

	fAlignment = new BOptionPopUp("alignment", "Alignment:",
		new BMessage(MSG_SV_ALIGN));
	fAlignment->AddOption("Left", B_ALIGN_LEFT);
	fAlignment->AddOption("Center", B_ALIGN_CENTER);
	fAlignment->AddOption("Right", B_ALIGN_RIGHT);
	fAlignment->SetValue(B_ALIGN_LEFT);

	fTruncation = new BOptionPopUp("truncation", "Truncation:",
		new BMessage(MSG_SV_TRUNCATE));
	fTruncation->AddOption("End", B_TRUNCATE_END);
	fTruncation->AddOption("Beginning", B_TRUNCATE_BEGINNING);
	fTruncation->AddOption("Middle", B_TRUNCATE_MIDDLE);
	fTruncation->SetValue(B_TRUNCATE_END);

	fBold = new BCheckBox("bold", "Bold font", new BMessage(MSG_SV_BOLD));

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fText)
		.Add(fAlignment)
		.Add(fTruncation)
		.Add(fBold)
		.View();
}


bool
StringViewPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_SV_TEXT:
			fString->SetText(fText->Text());
			LogEvent("SetText(\"%s\")", fText->Text());
			return true;

		case MSG_SV_ALIGN:
			fString->SetAlignment((alignment)fAlignment->Value());
			LogEvent("SetAlignment(%" B_PRId32 ")", fAlignment->Value());
			return true;

		case MSG_SV_TRUNCATE:
			fString->SetTruncation(fTruncation->Value());
			LogEvent("SetTruncation(%" B_PRId32 ")", fTruncation->Value());
			return true;

		case MSG_SV_BOLD:
		{
			bool bold = fBold->Value() == B_CONTROL_ON;
			fString->SetFont(bold ? be_bold_font : be_plain_font);
			fString->InvalidateLayout();
			fString->Invalidate();
			LogEvent("SetFont(%s)", bold ? "be_bold_font" : "be_plain_font");
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
