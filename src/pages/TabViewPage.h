/*
 * Haiku Gallery - BTabView page.
 */
#ifndef TAB_VIEW_PAGE_H
#define TAB_VIEW_PAGE_H

#include "GalleryPage.h"


class BOptionPopUp;
class BTabView;


class TabViewPage : public GalleryPage {
public:
								TabViewPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BTabView*			fTabView;
			BOptionPopUp*		fSide;
			BOptionPopUp*		fBorder;
};

#endif	// TAB_VIEW_PAGE_H
