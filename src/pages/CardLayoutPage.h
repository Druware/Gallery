/*
 * Haiku Gallery - BCardLayout / BCardView page.
 */
#ifndef CARD_LAYOUT_PAGE_H
#define CARD_LAYOUT_PAGE_H

#include "GalleryPage.h"


class BCardLayout;
class BOptionPopUp;


class CardLayoutPage : public GalleryPage {
public:
								CardLayoutPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			void				_Show(int32 index);

			BCardLayout*		fCards;
			BOptionPopUp*		fPick;
};

#endif	// CARD_LAYOUT_PAGE_H
