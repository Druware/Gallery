/*
 * Haiku Gallery - the navigation list on the left of the main window.
 */
#include "NavigationList.h"

#include <String.h>
#include <StringItem.h>

#include "PageRegistry.h"
#include "pages/GalleryPage.h"


namespace {

class NavItem : public BStringItem {
public:
	NavItem(const char* text, uint32 level, int32 pageIndex)
		:
		BStringItem(text, level, true),
		fPageIndex(pageIndex)
	{
	}

	int32 PageIndex() const
	{
		return fPageIndex;
	}

private:
	int32	fPageIndex;
};


bool
Matches(const char* text, const BString& filter)
{
	return filter.IsEmpty() || BString(text).IFindFirst(filter) >= 0;
}

}	// namespace


NavigationList::NavigationList()
	:
	BOutlineListView("navigation", B_SINGLE_SELECTION_LIST)
{
}


NavigationList::~NavigationList()
{
	_DeleteItems();
}


void
NavigationList::Populate(const std::vector<GalleryPage*>& pages,
	const char* filter)
{
	_DeleteItems();

	BString query(filter);
	query.Trim();

	if (Matches(pages[0]->Title(), query))
		AddItem(new NavItem(pages[0]->Title(), 0, 0));

	// Walk categories in registry order; each is listed once, followed by
	// its matching pages.
	std::vector<BString> seen;
	for (int32 i = 0; i < PageCount(); i++) {
		BString category(PageAt(i).category);
		bool known = false;
		for (size_t s = 0; s < seen.size(); s++) {
			if (seen[s] == category)
				known = true;
		}
		if (known)
			continue;
		seen.push_back(category);

		bool categoryMatches = !query.IsEmpty()
			&& category.IFindFirst(query) >= 0;
		NavItem* categoryItem = NULL;
		for (int32 j = i; j < PageCount(); j++) {
			if (category != PageAt(j).category)
				continue;
			GalleryPage* page = pages[j + 1];
			if (!categoryMatches && !Matches(page->Title(), query))
				continue;
			if (categoryItem == NULL) {
				categoryItem = new NavItem(category.String(), 0, -1);
				AddItem(categoryItem);
			}
			AddItem(new NavItem(page->Title(), 1, j + 1));
		}
	}
}


int32
NavigationList::SelectedPage() const
{
	int32 selection = CurrentSelection();
	if (selection < 0)
		return -1;
	return static_cast<NavItem*>(ItemAt(selection))->PageIndex();
}


void
NavigationList::SelectPage(int32 pageIndex)
{
	for (int32 i = 0; i < FullListCountItems(); i++) {
		NavItem* item = static_cast<NavItem*>(FullListItemAt(i));
		if (item->PageIndex() != pageIndex)
			continue;
		BListItem* super = Superitem(item);
		if (super != NULL && !super->IsExpanded())
			Expand(super);
		int32 index = IndexOf(item);
		if (index >= 0 && index != CurrentSelection()) {
			Select(index);
			ScrollToSelection();
		}
		return;
	}
	DeselectAll();
}


void
NavigationList::_DeleteItems()
{
	std::vector<BListItem*> items;
	for (int32 i = 0; i < FullListCountItems(); i++)
		items.push_back(FullListItemAt(i));
	MakeEmpty();
	for (size_t i = 0; i < items.size(); i++)
		delete items[i];
}
