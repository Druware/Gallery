/*
 * Haiku Gallery - the welcome page with a button for every control.
 */
#include "HomePage.h"

#include <Button.h>
#include <Font.h>
#include <GridLayout.h>
#include <GridView.h>
#include <LayoutBuilder.h>
#include <SeparatorView.h>
#include <SpaceLayoutItem.h>
#include <String.h>
#include <StringView.h>
#include <TextView.h>

#include "Messages.h"
#include "PageRegistry.h"


static const int32 kColumns = 4;


HomePage::HomePage(const std::vector<GalleryPage*>& controlPages)
	:
	GalleryPage("Home"),
	fControlPages(controlPages)
{
}


const char*
HomePage::Title() const
{
	return "Home";
}


const char*
HomePage::Description() const
{
	return "Welcome to Haiku Gallery, a tour of the controls in the Haiku "
		"Interface Kit and the Layout API. Pick a control from the list "
		"on the left, search for one by name, or press one of the buttons "
		"below. Every page has a live sample, options that change the "
		"sample while it runs, a line showing the last message the sample "
		"sent, and source code you can copy into your own application. "
		"Help \xE2\x96\xB8 Haiku Book opens the official API reference for "
		"the control you are looking at.";
}


const char*
HomePage::SourceSnippet() const
{
	return "";
}


const char*
HomePage::BookClass() const
{
	return NULL;
}


BView*
HomePage::CreateSample()
{
	return NULL;
}


void
HomePage::Build()
{
	BStringView* title = new BStringView("title", "Haiku Gallery");
	BFont titleFont(be_bold_font);
	titleFont.SetSize(titleFont.Size() * 2.0f);
	title->SetFont(&titleFont);

	BTextView* description = new BTextView("description");
	description->SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
	rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
	description->SetFontAndColor(be_plain_font, B_FONT_ALL, &textColor);
	description->SetText(Description());
	description->MakeEditable(false);
	description->SetWordWrap(true);
	description->SetExplicitMinSize(BSize(360, B_SIZE_UNSET));

	BGroupLayout* layout;
	BLayoutBuilder::Group<>(this, B_VERTICAL)
		.SetInsets(B_USE_WINDOW_SPACING)
		.GetLayout(&layout)
		.Add(title)
		.Add(description);

	// One labelled grid of buttons per category, in registry order.
	BString lastCategory;
	BGridLayout* grid = NULL;
	int32 cell = 0;
	for (int32 i = 0; i < PageCount(); i++) {
		BString category(PageAt(i).category);
		if (grid == NULL || category != lastCategory) {
			lastCategory = category;
			layout->AddView(new BSeparatorView(category.String(),
				B_HORIZONTAL, B_FANCY_BORDER,
				BAlignment(B_ALIGN_LEFT, B_ALIGN_VERTICAL_CENTER)));
			BGridView* gridView = new BGridView(B_USE_SMALL_SPACING,
				B_USE_SMALL_SPACING);
			grid = gridView->GridLayout();
			layout->AddView(gridView);
			cell = 0;
		}

		BMessage* message = new BMessage(MSG_SHOW_PAGE);
		message->AddInt32("index", i + 1);
		BButton* button = new BButton(fControlPages[i]->Title(),
			fControlPages[i]->Title(), message);
		button->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED, B_SIZE_UNSET));
		grid->AddView(button, cell % kColumns, cell / kColumns);
		cell++;
	}

	layout->AddItem(BSpaceLayoutItem::CreateGlue());
}
