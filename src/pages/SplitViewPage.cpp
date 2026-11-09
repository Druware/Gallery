/*
 * Haiku Gallery - BSplitView page.
 */
#include "SplitViewPage.h"

#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <Slider.h>
#include <SplitView.h>
#include <StringView.h>

#include "Messages.h"


static BView*
MakePane(const char* text)
{
	BStringView* label = new BStringView(text, text);
	label->SetAlignment(B_ALIGN_CENTER);
	label->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED, B_SIZE_UNLIMITED));
	label->SetViewUIColor(B_DOCUMENT_BACKGROUND_COLOR);
	label->SetExplicitMinSize(BSize(60, 60));
	return label;
}


SplitViewPage::SplitViewPage()
	:
	GalleryPage("BSplitView"),
	fSplit(NULL),
	fVertical(NULL),
	fCollapse(NULL),
	fSplitter(NULL)
{
}


const char*
SplitViewPage::Title() const
{
	return "BSplitView";
}


const char*
SplitViewPage::Description() const
{
	return "BSplitView lays out its children in a row or column with a "
		"draggable splitter between each pair. Weights set the initial "
		"split; collapsible items can be dragged, or set, to zero size. "
		"This window's navigation pane is a BSplitView item: View \xE2\x96\xB8 "
		"Show navigation collapses it.";
}


const char*
SplitViewPage::SourceSnippet() const
{
	return
"#include <LayoutBuilder.h>\n"
"#include <SplitView.h>\n"
"\n"
"BSplitView* split;\n"
"BLayoutBuilder::Group<>(this, B_VERTICAL)\n"
"\t.AddSplit(B_HORIZONTAL)\n"
"\t\t.GetSplitView(&split)\n"
"\t\t.Add(sidebar, 0.3f)\n"
"\t\t.Add(content, 0.7f)\n"
"\t.End();\n"
"\n"
"split->SetCollapsible(0, true);\n"
"split->SetItemCollapsed(0, true);  // hide the sidebar\n";
}


BView*
SplitViewPage::CreateSample()
{
	fSplit = new BSplitView(B_HORIZONTAL);
	BLayoutBuilder::Split<>(fSplit)
		.Add(MakePane("Left"), 0.3f)
		.Add(MakePane("Middle"), 0.4f)
		.Add(MakePane("Right"), 0.3f);
	fSplit->SetCollapsible(true);
	fSplit->SetExplicitMinSize(BSize(260, 120));
	return fSplit;
}


BView*
SplitViewPage::CreateOptions()
{
	fVertical = new BCheckBox("vertical", "Vertical",
		new BMessage(MSG_SP_VERTICAL));
	fCollapse = new BCheckBox("collapse", "Collapse left pane",
		new BMessage(MSG_SP_COLLAPSE));
	fSplitter = new BSlider("splitter", "Splitter size",
		new BMessage(MSG_SP_SPLITTER), 2, 20, B_HORIZONTAL);
	fSplitter->SetModificationMessage(new BMessage(MSG_SP_SPLITTER));
	fSplitter->SetValue((int32)fSplit->SplitterSize());

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fVertical)
		.Add(fCollapse)
		.Add(fSplitter)
		.View();
}


bool
SplitViewPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_SP_VERTICAL:
		{
			bool vertical = fVertical->Value() == B_CONTROL_ON;
			fSplit->SetOrientation(vertical ? B_VERTICAL : B_HORIZONTAL);
			LogEvent("SetOrientation(%s)",
				vertical ? "B_VERTICAL" : "B_HORIZONTAL");
			return true;
		}

		case MSG_SP_COLLAPSE:
		{
			bool collapse = fCollapse->Value() == B_CONTROL_ON;
			fSplit->SetItemCollapsed(0, collapse);
			LogEvent("SetItemCollapsed(0, %s)", collapse ? "true" : "false");
			return true;
		}

		case MSG_SP_SPLITTER:
			fSplit->SetSplitterSize(fSplitter->Value());
			LogEvent("SetSplitterSize(%" B_PRId32 ")", fSplitter->Value());
			return true;
	}
	return GalleryPage::HandleMessage(message);
}
