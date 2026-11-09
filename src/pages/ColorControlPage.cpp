/*
 * Haiku Gallery - BColorControl page.
 */
#include "ColorControlPage.h"

#include <CheckBox.h>
#include <ColorControl.h>
#include <LayoutBuilder.h>
#include <OptionPopUp.h>

#include "Messages.h"


ColorControlPage::ColorControlPage()
	:
	GalleryPage("BColorControl"),
	fColor(NULL),
	fSwatch(NULL),
	fLayout(NULL),
	fCellSize(NULL),
	fEnabled(NULL)
{
}


const char*
ColorControlPage::Title() const
{
	return "BColorControl";
}


const char*
ColorControlPage::Description() const
{
	return "BColorControl is Haiku's built-in color picker: red, green and "
		"blue ramps plus text fields for exact values (on screens with "
		"fewer colors it shows a palette instead). Value() packs the color "
		"into an int32, and ValueAsColor() returns it as an rgb_color. The "
		"swatch next to it follows the current color.";
}


const char*
ColorControlPage::SourceSnippet() const
{
	return
"#include <ColorControl.h>\n"
"\n"
"// The BPoint is ignored when the control is placed in a layout.\n"
"BColorControl* picker = new BColorControl(B_ORIGIN, B_CELLS_32x8,\n"
"\t8.0f, \"color\", new BMessage(MSG_COLOR_CHANGED));\n"
"picker->SetValue(make_color(0, 104, 214));\n"
"\n"
"// In MessageReceived():\n"
"case MSG_COLOR_CHANGED:\n"
"{\n"
"\trgb_color color = picker->ValueAsColor();\n"
"\tswatch->SetViewColor(color);\n"
"\tswatch->Invalidate();\n"
"\tbreak;\n"
"}\n";
}


BView*
ColorControlPage::CreateSample()
{
	fColor = new BColorControl(B_ORIGIN, B_CELLS_32x8, 8.0f, "color",
		new BMessage(MSG_CC_CHANGED));
	fColor->SetValue(make_color(0, 104, 214));

	fSwatch = new BView("swatch", B_WILL_DRAW);
	fSwatch->SetExplicitMinSize(BSize(48, 48));
	fSwatch->SetExplicitMaxSize(BSize(48, 48));
	_UpdateSwatch();

	return BLayoutBuilder::Group<>(B_HORIZONTAL)
		.Add(fColor)
		.Add(fSwatch)
		.AddGlue()
		.View();
}


BView*
ColorControlPage::CreateOptions()
{
	fLayout = new BOptionPopUp("layout", "Cells:",
		new BMessage(MSG_CC_LAYOUT));
	fLayout->AddOption("32 \xC3\x97 8", B_CELLS_32x8);
	fLayout->AddOption("16 \xC3\x97 16", B_CELLS_16x16);
	fLayout->AddOption("64 \xC3\x97 4", B_CELLS_64x4);
	fLayout->SetValue(B_CELLS_32x8);

	fCellSize = new BOptionPopUp("cellSize", "Cell size:",
		new BMessage(MSG_CC_CELLSIZE));
	fCellSize->AddOption("4 px", 4);
	fCellSize->AddOption("6 px", 6);
	fCellSize->AddOption("8 px", 8);
	fCellSize->SetValue(8);

	fEnabled = new BCheckBox("enabled", "Enabled",
		new BMessage(MSG_CC_ENABLED));
	fEnabled->SetValue(B_CONTROL_ON);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fLayout)
		.Add(fCellSize)
		.Add(fEnabled)
		.View();
}


void
ColorControlPage::_UpdateSwatch()
{
	fSwatch->SetViewColor(fColor->ValueAsColor());
	fSwatch->Invalidate();
}


bool
ColorControlPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_CC_CHANGED:
		{
			rgb_color color = fColor->ValueAsColor();
			_UpdateSwatch();
			LogEvent("Color: #%02X%02X%02X", color.red, color.green,
				color.blue);
			return true;
		}

		case MSG_CC_LAYOUT:
			fColor->SetLayout((color_control_layout)fLayout->Value());
			fColor->InvalidateLayout();
			LogEvent("SetLayout(%" B_PRId32 " columns)", fLayout->Value());
			return true;

		case MSG_CC_CELLSIZE:
			fColor->SetCellSize(fCellSize->Value());
			fColor->InvalidateLayout();
			LogEvent("SetCellSize(%" B_PRId32 ")", fCellSize->Value());
			return true;

		case MSG_CC_ENABLED:
		{
			bool enabled = fEnabled->Value() == B_CONTROL_ON;
			fColor->SetEnabled(enabled);
			LogEvent("SetEnabled(%s)", enabled ? "true" : "false");
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
