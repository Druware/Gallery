/*
 * Haiku Gallery - the navigation list on the left of the main window.
 *
 * Categories are top-level, expandable items; each page is an item
 * under its category. Populate() rebuilds the tree, keeping only pages
 * whose title or category contains the search filter.
 */
#ifndef NAVIGATION_LIST_H
#define NAVIGATION_LIST_H

#include <OutlineListView.h>

#include <vector>


class GalleryPage;


class NavigationList : public BOutlineListView {
public:
								NavigationList();
	virtual						~NavigationList();

			// pages[0] is the home page; pages[i] for i > 0 is
			// PageAt(i - 1) of the registry.
			void				Populate(
									const std::vector<GalleryPage*>& pages,
									const char* filter);

			// Page index of the selected item, or -1 for none or a
			// category item.
			int32				SelectedPage() const;
			void				SelectPage(int32 pageIndex);

private:
			void				_DeleteItems();
};

#endif	// NAVIGATION_LIST_H
