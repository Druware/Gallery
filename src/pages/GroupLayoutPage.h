/*
 * Haiku Gallery - BGroupLayout page.
 */
#ifndef GROUP_LAYOUT_PAGE_H
#define GROUP_LAYOUT_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BGroupLayout;
class BSlider;


class GroupLayoutPage : public GalleryPage {
public:
								GroupLayoutPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BGroupLayout*		fGroup;
			BCheckBox*			fVertical;
			BSlider*			fSpacing;
			BSlider*			fInsets;
			BCheckBox*			fWeights;
};

#endif	// GROUP_LAYOUT_PAGE_H
