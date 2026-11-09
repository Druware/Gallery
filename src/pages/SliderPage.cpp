/*
 * Haiku Gallery - BSlider page.
 */
#include "SliderPage.h"

#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <OptionPopUp.h>
#include <Slider.h>

#include "Messages.h"


SliderPage::SliderPage()
	:
	GalleryPage("BSlider"),
	fSlider(NULL),
	fVertical(NULL),
	fHashMarks(NULL),
	fTriangle(NULL),
	fFill(NULL),
	fEnabled(NULL)
{
}


const char*
SliderPage::Title() const
{
	return "BSlider";
}


const char*
SliderPage::Description() const
{
	return "BSlider picks an integer between a minimum and a maximum by "
		"dragging a thumb along a bar. It sends its message when the user "
		"lets go of the thumb, and its modification message continuously "
		"while dragging. Hash marks, limit labels, thumb style, bar fill "
		"color and orientation can all be changed at run time.";
}


const char*
SliderPage::SourceSnippet() const
{
	return
"#include <Slider.h>\n"
"\n"
"BSlider* slider = new BSlider(\"volume\", \"Volume\",\n"
"\tnew BMessage(MSG_CHANGED), 0, 100, B_HORIZONTAL);\n"
"slider->SetModificationMessage(new BMessage(MSG_DRAGGING));\n"
"slider->SetHashMarks(B_HASH_MARKS_BOTTOM);\n"
"slider->SetHashMarkCount(11);\n"
"slider->SetLimitLabels(\"Quiet\", \"Loud\");\n"
"slider->SetValue(50);\n"
"\n"
"rgb_color fill = ui_color(B_CONTROL_HIGHLIGHT_COLOR);\n"
"slider->UseFillColor(true, &fill);\n";
}


BView*
SliderPage::CreateSample()
{
	fSlider = new BSlider("slider", "Volume", new BMessage(MSG_SL_CHANGED),
		0, 100, B_HORIZONTAL);
	fSlider->SetModificationMessage(new BMessage(MSG_SL_MODIFIED));
	fSlider->SetHashMarks(B_HASH_MARKS_BOTTOM);
	fSlider->SetHashMarkCount(11);
	fSlider->SetLimitLabels("Quiet", "Loud");
	fSlider->SetValue(50);
	fSlider->SetKeyIncrementValue(5);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fSlider)
		.View();
}


BView*
SliderPage::CreateOptions()
{
	fVertical = new BCheckBox("vertical", "Vertical",
		new BMessage(MSG_SL_VERTICAL));
	fHashMarks = new BOptionPopUp("hashMarks", "Hash marks:",
		new BMessage(MSG_SL_HASHMARKS));
	fHashMarks->AddOption("None", B_HASH_MARKS_NONE);
	fHashMarks->AddOption("Top / left", B_HASH_MARKS_TOP);
	fHashMarks->AddOption("Bottom / right", B_HASH_MARKS_BOTTOM);
	fHashMarks->AddOption("Both", B_HASH_MARKS_BOTH);
	fHashMarks->SetValue(B_HASH_MARKS_BOTTOM);
	fTriangle = new BCheckBox("triangle", "Triangle thumb",
		new BMessage(MSG_SL_TRIANGLE));
	fFill = new BCheckBox("fill", "Fill bar with highlight color",
		new BMessage(MSG_SL_FILL));
	fEnabled = new BCheckBox("enabled", "Enabled",
		new BMessage(MSG_SL_ENABLED));
	fEnabled->SetValue(B_CONTROL_ON);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fVertical)
		.Add(fHashMarks)
		.Add(fTriangle)
		.Add(fFill)
		.Add(fEnabled)
		.View();
}


bool
SliderPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_SL_CHANGED:
			LogEvent("Value changed: %" B_PRId32, fSlider->Value());
			return true;

		case MSG_SL_MODIFIED:
			LogEvent("Dragging: %" B_PRId32, fSlider->Value());
			return true;

		case MSG_SL_VERTICAL:
		{
			bool vertical = fVertical->Value() == B_CONTROL_ON;
			fSlider->SetOrientation(vertical ? B_VERTICAL : B_HORIZONTAL);
			fSlider->InvalidateLayout();
			fSlider->Invalidate();
			LogEvent("SetOrientation(%s)",
				vertical ? "B_VERTICAL" : "B_HORIZONTAL");
			return true;
		}

		case MSG_SL_HASHMARKS:
			fSlider->SetHashMarks((hash_mark_location)fHashMarks->Value());
			LogEvent("SetHashMarks(%" B_PRId32 ")", fHashMarks->Value());
			return true;

		case MSG_SL_TRIANGLE:
		{
			bool triangle = fTriangle->Value() == B_CONTROL_ON;
			fSlider->SetStyle(triangle ? B_TRIANGLE_THUMB : B_BLOCK_THUMB);
			fSlider->Invalidate();
			LogEvent("SetStyle(%s)",
				triangle ? "B_TRIANGLE_THUMB" : "B_BLOCK_THUMB");
			return true;
		}

		case MSG_SL_FILL:
		{
			bool fill = fFill->Value() == B_CONTROL_ON;
			rgb_color color = ui_color(B_CONTROL_HIGHLIGHT_COLOR);
			fSlider->UseFillColor(fill, &color);
			fSlider->Invalidate();
			LogEvent("UseFillColor(%s)", fill ? "true" : "false");
			return true;
		}

		case MSG_SL_ENABLED:
		{
			bool enabled = fEnabled->Value() == B_CONTROL_ON;
			fSlider->SetEnabled(enabled);
			LogEvent("SetEnabled(%s)", enabled ? "true" : "false");
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
