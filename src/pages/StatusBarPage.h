/*
 * Haiku Gallery - BStatusBar page.
 */
#ifndef STATUS_BAR_PAGE_H
#define STATUS_BAR_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BMessageRunner;
class BOptionPopUp;
class BStatusBar;


class StatusBarPage : public GalleryPage {
public:
								StatusBarPage();
	virtual						~StatusBarPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			void				_Step(float delta);
			void				_Reset();

			BStatusBar*			fStatusBar;
			BCheckBox*			fAnimate;
			BOptionPopUp*		fColor;
			BMessageRunner*		fRunner;
};

#endif	// STATUS_BAR_PAGE_H
