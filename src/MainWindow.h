/*
 * Haiku Gallery - the main window: menu bar, navigation pane with a
 * search field, and a card view holding one page per control.
 */
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <Window.h>

#include <vector>


class BCardView;
class BMenuBar;
class BMenuItem;
class BSplitView;
class BTextControl;
class GalleryPage;
class NavigationList;


class MainWindow : public BWindow {
public:
								MainWindow();

	virtual	void				MessageReceived(BMessage* message);

private:
			BMenuBar*			_BuildMenuBar();
			void				_ShowPage(int32 index);
			void				_OpenDocsFolder();
			void				_OpenBookPage();
			bool				_DispatchToPages(BMessage* message);

			std::vector<GalleryPage*> fPages;
			int32				fCurrentPage;

			NavigationList*		fNavList;
			BTextControl*		fSearch;
			BSplitView*			fSplit;
			BCardView*			fCards;
			BMenuItem*			fShowNavItem;
};

#endif	// MAIN_WINDOW_H
