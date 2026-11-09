/*
 * Haiku Gallery - BBox page.
 */
#ifndef BOX_PAGE_H
#define BOX_PAGE_H

#include "GalleryPage.h"


class BBox;
class BCheckBox;
class BOptionPopUp;
class BTextControl;


class BoxPage : public GalleryPage {
public:
								BoxPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			void				_UpdateLabel();

			BBox*				fBox;
			BView*				fContent;
			BOptionPopUp*		fBorder;
			BTextControl*		fLabel;
			BCheckBox*			fViewLabel;
};

#endif	// BOX_PAGE_H
