/*
 * Haiku Gallery - BOutlineListView page.
 */
#ifndef OUTLINE_LIST_VIEW_PAGE_H
#define OUTLINE_LIST_VIEW_PAGE_H

#include "GalleryPage.h"


class BOutlineListView;


class OutlineListViewPage : public GalleryPage {
public:
								OutlineListViewPage();
	virtual						~OutlineListViewPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BOutlineListView*	fOutline;
			int32				fAdded;
};

#endif	// OUTLINE_LIST_VIEW_PAGE_H
