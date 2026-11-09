/*
 * Haiku Gallery - abstract base class for one gallery page.
 */
#include "GalleryPage.h"

#include <stdarg.h>

#include <Box.h>
#include <Button.h>
#include <Clipboard.h>
#include <Font.h>
#include <LayoutBuilder.h>
#include <ScrollView.h>
#include <String.h>
#include <StringView.h>
#include <TextView.h>

#include "Messages.h"


GalleryPage::GalleryPage(const char* name)
	:
	BView(name, 0),
	fEventLine(NULL),
	fSourceView(NULL)
{
	SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
}


GalleryPage::~GalleryPage()
{
}


const char*
GalleryPage::BookClass() const
{
	return Title();
}


BView*
GalleryPage::CreateOptions()
{
	return NULL;
}


static BBox*
MakeBox(const char* label, BView* content)
{
	BBox* box = new BBox(label);
	box->SetLabel(label);
	box->AddChild(BLayoutBuilder::Group<>(B_VERTICAL)
		.SetInsets(B_USE_DEFAULT_SPACING)
		.Add(content)
		.AddGlue()
		.View());
	return box;
}


void
GalleryPage::Build()
{
	BStringView* title = new BStringView("title", Title());
	BFont titleFont(be_bold_font);
	titleFont.SetSize(titleFont.Size() * 1.6f);
	title->SetFont(&titleFont);

	BTextView* description = new BTextView("description");
	description->SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
	rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
	description->SetFontAndColor(be_plain_font, B_FONT_ALL, &textColor);
	description->SetText(Description());
	description->MakeEditable(false);
	description->SetWordWrap(true);
	description->SetExplicitMinSize(BSize(360, B_SIZE_UNSET));

	fEventLine = new BStringView("eventLine", "Events: (none yet)");
	fEventLine->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED, B_SIZE_UNSET));

	fSourceView = new BTextView("source");
	fSourceView->SetText(SourceSnippet());
	fSourceView->SetFontAndColor(be_fixed_font);
	fSourceView->MakeEditable(false);
	fSourceView->SetWordWrap(false);
	BScrollView* sourceScroll = new BScrollView("sourceScroll", fSourceView,
		0, true, true);
	sourceScroll->SetExplicitMinSize(BSize(B_SIZE_UNSET, 150));

	BButton* copyButton = new BButton("copy", "Copy source",
		new BMessage(MSG_COPY_SOURCE));

	// Only the source box takes extra height (weight 1); everything above
	// it keeps its preferred height (weight 0).
	BGroupLayout* samples;
	BLayoutBuilder::Group<>(this, B_VERTICAL)
		.SetInsets(B_USE_WINDOW_SPACING)
		.Add(title, 0.0f)
		.Add(description, 0.0f)
		.AddGroup(B_HORIZONTAL, B_USE_DEFAULT_SPACING, 0.0f)
			.GetLayout(&samples)
			.Add(MakeBox("Sample", CreateSample()), 2.0f)
		.End()
		.Add(fEventLine, 0.0f)
		.AddGroup(B_HORIZONTAL, B_USE_DEFAULT_SPACING, 0.0f)
			.Add(new BStringView("sourceLabel", "Source"))
			.AddGlue()
			.Add(copyButton)
		.End()
		.Add(sourceScroll, 1.0f);

	BView* options = CreateOptions();
	if (options != NULL)
		samples->AddView(MakeBox("Options", options), 1.0f);
}


bool
GalleryPage::HandleMessage(BMessage* message)
{
	if (message->what == MSG_COPY_SOURCE && fSourceView != NULL) {
		fSourceView->SelectAll();
		fSourceView->Copy(be_clipboard);
		LogEvent("Source copied to the clipboard");
		return true;
	}
	return false;
}


void
GalleryPage::LogEvent(const char* format, ...)
{
	if (fEventLine == NULL)
		return;

	va_list args;
	va_start(args, format);
	BString text;
	text.SetToFormatVarArgs(format, args);
	va_end(args);

	text.Prepend("Last event: ");
	fEventLine->SetText(text.String());
}
