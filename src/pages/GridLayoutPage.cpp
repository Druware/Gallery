/*
 * Haiku Gallery - BGridLayout page.
 */
#include "GridLayoutPage.h"

#include <Button.h>
#include <CheckBox.h>
#include <GridLayout.h>
#include <GridView.h>
#include <LayoutBuilder.h>
#include <MenuField.h>
#include <MenuItem.h>
#include <PopUpMenu.h>
#include <Slider.h>
#include <TextControl.h>

#include "Messages.h"


GridLayoutPage::GridLayoutPage()
	:
	GalleryPage("BGridLayout"),
	fGrid(NULL),
	fHorizontal(NULL),
	fVertical(NULL),
	fWeight(NULL)
{
}


const char*
GridLayoutPage::Title() const
{
	return "BGridLayout";
}


const char*
GridLayoutPage::Description() const
{
	return "BGridLayout places items in rows and columns; an item can span "
		"several cells. It is the natural layout for forms: "
		"AddTextControl() and AddMenuField() put a control's label in one "
		"column and its field in the next, so labels line up. Column and "
		"row weights decide which ones grow.";
}


const char*
GridLayoutPage::SourceSnippet() const
{
	return
"#include <LayoutBuilder.h>\n"
"\n"
"BLayoutBuilder::Grid<>(this, B_USE_DEFAULT_SPACING,\n"
"\t\tB_USE_SMALL_SPACING)\n"
"\t.SetInsets(B_USE_WINDOW_INSETS)\n"
"\t.AddTextControl(firstName, 0, 0)   // columns 0 and 1\n"
"\t.AddTextControl(lastName, 0, 1)\n"
"\t.AddMenuField(country, 0, 2)\n"
"\t.Add(okButton, 1, 3)               // column 1, row 3\n"
"\t.SetColumnWeight(1, 2.0f);\n"
"\n"
"BGridLayout* grid = (BGridLayout*)GetLayout();\n"
"grid->SetSpacing(10, 4);\n";
}


BView*
GridLayoutPage::CreateSample()
{
	BPopUpMenu* menu = new BPopUpMenu("country");
	menu->AddItem(new BMenuItem("Germany", NULL));
	menu->AddItem(new BMenuItem("Japan", NULL));
	menu->AddItem(new BMenuItem("United States", NULL));
	menu->ItemAt(0)->SetMarked(true);

	BGridView* gridView = new BGridView();
	fGrid = gridView->GridLayout();
	BLayoutBuilder::Grid<>(fGrid)
		.SetInsets(0)
		.AddTextControl(new BTextControl("first", "First name:", "", NULL),
			0, 0)
		.AddTextControl(new BTextControl("last", "Last name:", "", NULL),
			0, 1)
		.AddMenuField(new BMenuField("country", "Country:", menu), 0, 2)
		.Add(new BButton("wide", "Spans two columns", NULL), 0, 3, 2, 1);

	return gridView;
}


BView*
GridLayoutPage::CreateOptions()
{
	fHorizontal = new BSlider("hspacing", "Horizontal spacing",
		new BMessage(MSG_GR_HSPACING), 0, 30, B_HORIZONTAL);
	fHorizontal->SetModificationMessage(new BMessage(MSG_GR_HSPACING));
	fHorizontal->SetValue(5);
	fVertical = new BSlider("vspacing", "Vertical spacing",
		new BMessage(MSG_GR_VSPACING), 0, 30, B_HORIZONTAL);
	fVertical->SetModificationMessage(new BMessage(MSG_GR_VSPACING));
	fVertical->SetValue(5);
	fWeight = new BCheckBox("weight", "Label column grows too",
		new BMessage(MSG_GR_WEIGHT));

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fHorizontal)
		.Add(fVertical)
		.Add(fWeight)
		.View();
}


bool
GridLayoutPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_GR_HSPACING:
			fGrid->SetHorizontalSpacing(fHorizontal->Value());
			LogEvent("SetHorizontalSpacing(%" B_PRId32 ")",
				fHorizontal->Value());
			return true;

		case MSG_GR_VSPACING:
			fGrid->SetVerticalSpacing(fVertical->Value());
			LogEvent("SetVerticalSpacing(%" B_PRId32 ")", fVertical->Value());
			return true;

		case MSG_GR_WEIGHT:
		{
			bool grow = fWeight->Value() == B_CONTROL_ON;
			fGrid->SetColumnWeight(0, grow ? 1.0f : 0.0f);
			LogEvent("SetColumnWeight(0, %s)", grow ? "1.0" : "0.0");
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
