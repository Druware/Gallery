/*
 * Haiku Gallery - BScrollView page.
 */
#include "ScrollViewPage.h"

#include <string.h>

#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <OptionPopUp.h>
#include <ScrollBar.h>
#include <ScrollView.h>
#include <String.h>
#include <TextView.h>

#include "Messages.h"


ScrollViewPage::ScrollViewPage()
	:
	GalleryPage("BScrollView"),
	fScroll(NULL),
	fBorder(NULL),
	fHighlight(NULL)
{
}


const char*
ScrollViewPage::Title() const
{
	return "BScrollView";
}


const char*
ScrollViewPage::Description() const
{
	return "BScrollView wraps a target view, adds horizontal and/or "
		"vertical BScrollBar objects and draws a border around both. The "
		"target decides how far it can scroll: list and text views update "
		"the scroll bars themselves; a custom view sets the range with "
		"BScrollBar::SetRange() and SetProportion().";
}


const char*
ScrollViewPage::SourceSnippet() const
{
	return
"#include <ScrollView.h>\n"
"\n"
"// Scroll bars are chosen when the scroll view is created:\n"
"BScrollView* scroll = new BScrollView(\"scroll\", textView,\n"
"\t0, true /* horizontal */, true /* vertical */,\n"
"\tB_FANCY_BORDER);\n"
"\n"
"// Show it as focused, e.g. while the target has focus:\n"
"scroll->SetBorderHighlighted(true);\n"
"\n"
"// For a custom target, tell the scroll bar its range:\n"
"BScrollBar* bar = scroll->ScrollBar(B_VERTICAL);\n"
"bar->SetRange(0, dataHeight - Bounds().Height());\n"
"bar->SetProportion(Bounds().Height() / dataHeight);\n";
}


BView*
ScrollViewPage::CreateSample()
{
	BString text;
	for (int32 i = 1; i <= 40; i++) {
		text << "Line " << i << ": a long line of text that is wider than "
			"the view, so the horizontal scroll bar has something to do.\n";
	}

	BTextView* target = new BTextView("target");
	target->SetText(text.String());
	target->SetWordWrap(false);
	target->MakeEditable(false);

	fScroll = new BScrollView("scroll", target, 0, true, true);
	fScroll->SetExplicitMinSize(BSize(260, 140));

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fScroll)
		.View();
}


BView*
ScrollViewPage::CreateOptions()
{
	fBorder = new BOptionPopUp("border", "Border:",
		new BMessage(MSG_SC_BORDER));
	fBorder->AddOption("Fancy", B_FANCY_BORDER);
	fBorder->AddOption("Plain", B_PLAIN_BORDER);
	fBorder->AddOption("None", B_NO_BORDER);
	fBorder->SetValue(B_FANCY_BORDER);

	fHighlight = new BCheckBox("highlight", "Highlight border",
		new BMessage(MSG_SC_HIGHLIGHT));

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fBorder)
		.Add(fHighlight)
		.View();
}


bool
ScrollViewPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_SC_BORDER:
			fScroll->SetBorder((border_style)fBorder->Value());
			LogEvent("SetBorder(%" B_PRId32 ")", fBorder->Value());
			return true;

		case MSG_SC_HIGHLIGHT:
		{
			bool highlight = fHighlight->Value() == B_CONTROL_ON;
			status_t status = fScroll->SetBorderHighlighted(highlight);
			LogEvent("SetBorderHighlighted(%s): %s",
				highlight ? "true" : "false", strerror(status));
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
