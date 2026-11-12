/*
 * Haiku Gallery - the main window.
 */
#include "MainWindow.h"

#include <Alert.h>
#include <Application.h>
#include <CardLayout.h>
#include <CardView.h>
#include <Entry.h>
#include <LayoutBuilder.h>
#include <MenuBar.h>
#include <MenuItem.h>
#include <Messenger.h>
#include <Path.h>
#include <Roster.h>
#include <ScrollView.h>
#include <SplitView.h>
#include <String.h>
#include <TextControl.h>

#include "Messages.h"
#include "NavigationList.h"
#include "PageRegistry.h"
#include "pages/GalleryPage.h"
#include "pages/HomePage.h"


static const char* kWindowTitle = "Haiku Gallery";
static const char* kTrackerSignature = "application/x-vnd.Be-TRAK";
static const char* kBookBaseURL = "https://www.haiku-os.org/docs/api/";


MainWindow::MainWindow()
	:
	// The frame is only a starting size; the layout sets the limits.
	BWindow(BRect(0, 0, 1000, 720), kWindowTitle, B_TITLED_WINDOW,
		B_AUTO_UPDATE_SIZE_LIMITS | B_QUIT_ON_WINDOW_CLOSE
			| B_ASYNCHRONOUS_CONTROLS),
	fCurrentPage(-1),
	fShowNavItem(NULL)
{
	std::vector<GalleryPage*> controlPages;
	for (int32 i = 0; i < PageCount(); i++)
		controlPages.push_back(PageAt(i).create());

	fPages.push_back(new HomePage(controlPages));
	fPages.insert(fPages.end(), controlPages.begin(), controlPages.end());

	fCards = new BCardView("content");
	for (size_t i = 0; i < fPages.size(); i++) {
		fPages[i]->Build();
		fCards->CardLayout()->AddView(fPages[i]);
	}

	fSearch = new BTextControl("search", "Search:", "", NULL);
	fSearch->SetModificationMessage(new BMessage(MSG_SEARCH_CHANGED));
	fSearch->SetToolTip("Filter the list by control or category name");

	fNavList = new NavigationList();
	fNavList->SetSelectionMessage(new BMessage(MSG_NAV_SELECTED));
	BScrollView* navScroll = new BScrollView("navScroll", fNavList, 0,
		false, true);
	navScroll->SetExplicitMinSize(BSize(190, B_SIZE_UNSET));

	BMenuBar* menuBar = _BuildMenuBar();
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.Add(menuBar)
		.AddSplit(B_HORIZONTAL, B_USE_SMALL_SPACING)
			.GetSplitView(&fSplit)
			.AddGroup(B_VERTICAL, B_USE_SMALL_SPACING, 0.25f)
				.SetInsets(B_USE_WINDOW_SPACING, B_USE_WINDOW_SPACING, 0,
					B_USE_WINDOW_SPACING)
				.Add(fSearch)
				.Add(navScroll)
			.End()
			.Add(fCards, 0.75f)
		.End();

	// The MenuBar sample page has a BMenuBar of its own; make sure the
	// real one is the window's key menu bar.
	SetKeyMenuBar(menuBar);

	fSplit->SetCollapsible(0, true);
	fSplit->SetCollapsible(1, false);

	fNavList->Populate(fPages, "");
	_ShowPage(0);
	fNavList->SelectPage(0);

	CenterOnScreen();
}


void
MainWindow::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case MSG_NAV_SELECTED:
		{
			int32 index = fNavList->SelectedPage();
			if (index >= 0)
				_ShowPage(index);
			break;
		}

		case MSG_SHOW_PAGE:
		{
			int32 index;
			if (message->FindInt32("index", &index) == B_OK) {
				_ShowPage(index);
				fNavList->SelectPage(index);
			}
			break;
		}

		case MSG_GO_HOME:
			_ShowPage(0);
			fNavList->SelectPage(0);
			break;

		case MSG_SEARCH_CHANGED:
			fNavList->Populate(fPages, fSearch->Text());
			fNavList->SelectPage(fCurrentPage);
			break;

		case MSG_FOCUS_SEARCH:
			fSearch->MakeFocus(true);
			break;

		case MSG_TOGGLE_NAV:
		{
			bool show = fSplit->IsItemCollapsed(0);
			fSplit->SetItemCollapsed(0, !show);
			fShowNavItem->SetMarked(show);
			break;
		}

		case MSG_OPEN_DOCS:
			_OpenDocsFolder();
			break;

		case MSG_OPEN_BOOK:
			_OpenBookPage();
			break;

		case B_ABOUT_REQUESTED:
			be_app->PostMessage(B_ABOUT_REQUESTED);
			break;

		default:
			if (!_DispatchToPages(message))
				BWindow::MessageReceived(message);
			break;
	}
}


BMenuBar*
MainWindow::_BuildMenuBar()
{
	BMenuBar* menuBar = new BMenuBar("menuBar");

	BLayoutBuilder::Menu<>(menuBar)
		.AddMenu("File")
			.AddItem("About Haiku Gallery" B_UTF8_ELLIPSIS, B_ABOUT_REQUESTED)
			.AddSeparator()
			.AddItem("Quit", B_QUIT_REQUESTED, 'Q')
		.End()
		.AddMenu("View")
			.AddItem("Home", MSG_GO_HOME, 'H')
			.AddItem("Show navigation", MSG_TOGGLE_NAV, 'N')
				.GetItem(fShowNavItem)
			.AddItem("Find control" B_UTF8_ELLIPSIS, MSG_FOCUS_SEARCH, 'F')
		.End()
		.AddMenu("Help")
			.AddItem("Open documentation folder", MSG_OPEN_DOCS)
			.AddItem("Haiku Book page for this control", MSG_OPEN_BOOK, 'B')
			.AddSeparator()
			.AddItem("About Haiku Gallery" B_UTF8_ELLIPSIS, B_ABOUT_REQUESTED)
		.End();

	fShowNavItem->SetMarked(true);
	return menuBar;
}


void
MainWindow::_ShowPage(int32 index)
{
	if (index < 0 || index >= (int32)fPages.size() || index == fCurrentPage)
		return;

	fCurrentPage = index;
	fCards->CardLayout()->SetVisibleItem(index);

	BString title(kWindowTitle);
	if (index > 0)
		title << " \xE2\x80\x94 " << fPages[index]->Title();
	SetTitle(title.String());
}


bool
MainWindow::_DispatchToPages(BMessage* message)
{
	// The visible page gets the first chance; asynchronous replies (file
	// panels, alerts, timers) may arrive after the user moved on, so the
	// others are asked too. Codes are unique per page (Messages.h).
	if (fCurrentPage >= 0 && fPages[fCurrentPage]->HandleMessage(message))
		return true;
	for (size_t i = 0; i < fPages.size(); i++) {
		if ((int32)i != fCurrentPage && fPages[i]->HandleMessage(message))
			return true;
	}
	return false;
}


void
MainWindow::_OpenDocsFolder()
{
	// Look for docs/ next to the executable, then one level up: a
	// makefile-engine build puts the binary in objects.*/ inside the
	// source tree, whose docs/ is in the parent directory.
	app_info info;
	BPath directory;
	entry_ref ref;
	bool found = false;
	if (be_app->GetAppInfo(&info) == B_OK
		&& directory.SetTo(&info.ref) == B_OK
		&& directory.GetParent(&directory) == B_OK) {
		for (int32 level = 0; level < 2 && !found; level++) {
			BPath docs(directory);
			found = docs.Append("docs") == B_OK
				&& get_ref_for_path(docs.Path(), &ref) == B_OK
				&& BEntry(&ref).Exists();
			if (!found && directory.GetParent(&directory) != B_OK)
				break;
		}
	}

	if (!found) {
		BAlert* alert = new BAlert("Documentation",
			"The docs folder was not found next to the application or in "
			"its parent folder.\n\n"
			"The documentation is in the docs/ folder of the source tree.",
			"OK", NULL, NULL, B_WIDTH_AS_USUAL, B_WARNING_ALERT);
		alert->Go(NULL);
		return;
	}

	BMessage refs(B_REFS_RECEIVED);
	refs.AddRef("refs", &ref);
	BMessenger(kTrackerSignature).SendMessage(&refs);
}


void
MainWindow::_OpenBookPage()
{
	BString url(kBookBaseURL);
	const char* bookClass = fCurrentPage >= 0
		? fPages[fCurrentPage]->BookClass() : NULL;
	if (bookClass != NULL)
		url << "class" << bookClass << ".html";

	const char* args[] = { url.String(), NULL };
	be_roster->Launch("application/x-vnd.Be.URL.https", 1, args);
}
