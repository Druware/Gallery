/*
 * Haiku Gallery - BListView page.
 */
#ifndef LIST_VIEW_PAGE_H
#define LIST_VIEW_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BListView;
class BTextControl;


class ListViewPage : public GalleryPage {
public:
								ListViewPage();
	virtual						~ListViewPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BListView*			fList;
			BCheckBox*			fMultiple;
			BTextControl*		fNewItem;
};

#endif	// LIST_VIEW_PAGE_H
