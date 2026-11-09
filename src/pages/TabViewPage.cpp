/*
 * Haiku Gallery - BTabView page.
 */
#include "TabViewPage.h"

#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <OptionPopUp.h>
#include <StringView.h>
#include <TabView.h>
#include <Window.h>

#include "Messages.h"


namespace {

// BTabView sends no message when the selection changes; this subclass
// reports it to the window.
class NotifyingTabView : public BTabView {
public:
	NotifyingTabView(const char* name)
		:
		BTabView(name, B_WIDTH_FROM_LABEL)
	{
	}

	virtual void Select(int32 index)
	{
		BTabView::Select(index);
		if (Window() != NULL) {
			BMessage message(MSG_TB_SELECTED);
			message.AddInt32("index", index);
			Window()->PostMessage(&message);
		}
	}
};

}	// namespace


TabViewPage::TabViewPage()
	:
	GalleryPage("BTabView"),
	fTabView(NULL),
	fSide(NULL),
	fBorder(NULL)
{
}


const char*
TabViewPage::Title() const
{
	return "BTabView";
}


const char*
TabViewPage::Description() const
{
	return "BTabView shows one of several views, chosen with a row of "
		"tabs. Each tab is a BTab that takes its label from its view's "
		"name. The tabs can sit on any side, and the frame can be fancy, "
		"plain or absent. There is no selection message: override "
		"Select() to be told when the user switches tabs.";
}


const char*
TabViewPage::SourceSnippet() const
{
	return
"#include <TabView.h>\n"
"\n"
"BTabView* tabs = new BTabView(\"tabs\", B_WIDTH_FROM_LABEL);\n"
"\n"
"// The tab label comes from the view's name.\n"
"BView* general = new BGroupView(\"General\");\n"
"BView* advanced = new BGroupView(\"Advanced\");\n"
"tabs->AddTab(general);\n"
"tabs->AddTab(advanced);\n"
"tabs->Select(0);\n"
"\n"
"tabs->SetTabSide(BTabView::kLeftSide);\n"
"tabs->SetBorder(B_PLAIN_BORDER);\n";
}


BView*
TabViewPage::CreateSample()
{
	fTabView = new NotifyingTabView("tabs");

	BView* general = BLayoutBuilder::Group<>(B_VERTICAL)
		.SetInsets(B_USE_DEFAULT_SPACING)
		.Add(new BCheckBox("autosave", "Save automatically", NULL))
		.Add(new BCheckBox("backup", "Keep a backup copy", NULL))
		.AddGlue()
		.View();
	general->SetName("General");

	BView* appearance = BLayoutBuilder::Group<>(B_VERTICAL)
		.SetInsets(B_USE_DEFAULT_SPACING)
		.Add(new BStringView("text", "Appearance settings go here."))
		.AddGlue()
		.View();
	appearance->SetName("Appearance");

	BView* advanced = BLayoutBuilder::Group<>(B_VERTICAL)
		.SetInsets(B_USE_DEFAULT_SPACING)
		.Add(new BStringView("text", "Here be dragons."))
		.AddGlue()
		.View();
	advanced->SetName("Advanced");

	fTabView->AddTab(general);
	fTabView->AddTab(appearance);
	fTabView->AddTab(advanced);
	fTabView->SetExplicitMinSize(BSize(280, 140));
	return fTabView;
}


BView*
TabViewPage::CreateOptions()
{
	fSide = new BOptionPopUp("side", "Tab side:", new BMessage(MSG_TB_SIDE));
	fSide->AddOption("Top", BTabView::kTopSide);
	fSide->AddOption("Bottom", BTabView::kBottomSide);
	fSide->AddOption("Left", BTabView::kLeftSide);
	fSide->AddOption("Right", BTabView::kRightSide);
	fSide->SetValue(BTabView::kTopSide);

	fBorder = new BOptionPopUp("border", "Border:",
		new BMessage(MSG_TB_BORDER));
	fBorder->AddOption("Fancy", B_FANCY_BORDER);
	fBorder->AddOption("Plain", B_PLAIN_BORDER);
	fBorder->AddOption("None", B_NO_BORDER);
	fBorder->SetValue(B_FANCY_BORDER);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fSide)
		.Add(fBorder)
		.View();
}


bool
TabViewPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_TB_SELECTED:
		{
			int32 index;
			if (message->FindInt32("index", &index) == B_OK
				&& fTabView->TabAt(index) != NULL) {
				LogEvent("Selected tab %" B_PRId32 " (\"%s\")", index,
					fTabView->TabAt(index)->Label());
			}
			return true;
		}

		case MSG_TB_SIDE:
			fTabView->SetTabSide((BTabView::tab_side)fSide->Value());
			LogEvent("SetTabSide(%" B_PRId32 ")", fSide->Value());
			return true;

		case MSG_TB_BORDER:
			fTabView->SetBorder((border_style)fBorder->Value());
			LogEvent("SetBorder(%" B_PRId32 ")", fBorder->Value());
			return true;
	}
	return GalleryPage::HandleMessage(message);
}
