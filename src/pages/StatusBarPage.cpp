/*
 * Haiku Gallery - BStatusBar page.
 */
#include "StatusBarPage.h"

#include <Button.h>
#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <MessageRunner.h>
#include <Messenger.h>
#include <OptionPopUp.h>
#include <StatusBar.h>
#include <String.h>
#include <Window.h>

#include "Messages.h"


StatusBarPage::StatusBarPage()
	:
	GalleryPage("BStatusBar"),
	fStatusBar(NULL),
	fAnimate(NULL),
	fColor(NULL),
	fRunner(NULL)
{
}


StatusBarPage::~StatusBarPage()
{
	delete fRunner;
}


const char*
StatusBarPage::Title() const
{
	return "BStatusBar";
}


const char*
StatusBarPage::Description() const
{
	return "BStatusBar is a progress bar with a label and trailing label "
		"above the bar and optional text next to each. Update() advances "
		"it by a delta (and can set the texts at the same time), Reset() "
		"starts over, and SetMaxValue() sets what counts as complete. A "
		"BMessageRunner drives the animation here.";
}


const char*
StatusBarPage::SourceSnippet() const
{
	return
"#include <MessageRunner.h>\n"
"#include <StatusBar.h>\n"
"\n"
"BStatusBar* progress = new BStatusBar(\"progress\", \"Copying\",\n"
"\t\"files\");\n"
"progress->SetMaxValue(100);\n"
"\n"
"// Tick ten times a second:\n"
"BMessageRunner* runner = new BMessageRunner(BMessenger(this),\n"
"\tBMessage(MSG_TICK), 100000);\n"
"\n"
"// In MessageReceived():\n"
"case MSG_TICK:\n"
"{\n"
"\tBString text;\n"
"\ttext.SetToFormat(\"%d%%\", (int)progress->CurrentValue() + 2);\n"
"\tprogress->Update(2, NULL, text.String());\n"
"\tbreak;\n"
"}\n";
}


BView*
StatusBarPage::CreateSample()
{
	fStatusBar = new BStatusBar("progress", "Copying", "files");
	fStatusBar->SetMaxValue(100);
	fStatusBar->SetExplicitMinSize(BSize(240, B_SIZE_UNSET));
	_Reset();

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fStatusBar)
		.AddGroup(B_HORIZONTAL)
			.Add(new BButton("step", "Step +10", new BMessage(MSG_SB_STEP)))
			.Add(new BButton("reset", "Reset", new BMessage(MSG_SB_RESET)))
			.AddGlue()
		.End()
		.View();
}


BView*
StatusBarPage::CreateOptions()
{
	fAnimate = new BCheckBox("animate", "Animate",
		new BMessage(MSG_SB_ANIMATE));
	fColor = new BOptionPopUp("color", "Bar color:",
		new BMessage(MSG_SB_COLOR));
	fColor->AddOption("Default", 0);
	fColor->AddOption("Green", 1);
	fColor->AddOption("Red", 2);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fAnimate)
		.Add(fColor)
		.View();
}


void
StatusBarPage::_Step(float delta)
{
	if (fStatusBar->CurrentValue() >= fStatusBar->MaxValue())
		_Reset();

	float value = fStatusBar->CurrentValue() + delta;
	if (value > fStatusBar->MaxValue())
		delta = fStatusBar->MaxValue() - fStatusBar->CurrentValue();

	BString text;
	text.SetToFormat("%d%%", (int)(fStatusBar->CurrentValue() + delta));
	fStatusBar->Update(delta, NULL, text.String());
}


void
StatusBarPage::_Reset()
{
	fStatusBar->Reset("Copying", "files");
	fStatusBar->SetMaxValue(100);
	fStatusBar->SetTrailingText("0%");
}


bool
StatusBarPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_SB_STEP:
			_Step(10);
			LogEvent("Update(10): now %.0f of %.0f",
				fStatusBar->CurrentValue(), fStatusBar->MaxValue());
			return true;

		case MSG_SB_RESET:
			_Reset();
			LogEvent("Reset()");
			return true;

		case MSG_SB_TICK:
			_Step(2);
			if (fStatusBar->CurrentValue() >= fStatusBar->MaxValue())
				LogEvent("Complete");
			return true;

		case MSG_SB_ANIMATE:
		{
			delete fRunner;
			fRunner = NULL;
			bool animate = fAnimate->Value() == B_CONTROL_ON;
			if (animate) {
				fRunner = new BMessageRunner(BMessenger(Window()),
					BMessage(MSG_SB_TICK), 100000);
			}
			LogEvent("Animation %s", animate ? "started" : "stopped");
			return true;
		}

		case MSG_SB_COLOR:
		{
			rgb_color color = ui_color(B_STATUS_BAR_COLOR);
			if (fColor->Value() == 1)
				color = make_color(60, 170, 60);
			else if (fColor->Value() == 2)
				color = make_color(210, 50, 50);
			fStatusBar->SetBarColor(color);
			LogEvent("SetBarColor(#%02X%02X%02X)", color.red, color.green,
				color.blue);
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
