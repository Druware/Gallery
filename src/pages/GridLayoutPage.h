/*
 * Haiku Gallery - BGridLayout page.
 */
#ifndef GRID_LAYOUT_PAGE_H
#define GRID_LAYOUT_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BGridLayout;
class BSlider;


class GridLayoutPage : public GalleryPage {
public:
								GridLayoutPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BGridLayout*		fGrid;
			BSlider*			fHorizontal;
			BSlider*			fVertical;
			BCheckBox*			fWeight;
};

#endif	// GRID_LAYOUT_PAGE_H
