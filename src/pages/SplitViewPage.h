/*
 * Haiku Gallery - BSplitView page.
 */
#ifndef SPLIT_VIEW_PAGE_H
#define SPLIT_VIEW_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BSlider;
class BSplitView;


class SplitViewPage : public GalleryPage {
public:
								SplitViewPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BSplitView*			fSplit;
			BCheckBox*			fVertical;
			BCheckBox*			fCollapse;
			BSlider*			fSplitter;
};

#endif	// SPLIT_VIEW_PAGE_H
