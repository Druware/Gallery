/*
 * Haiku Gallery - BAlert page.
 */
#ifndef ALERT_PAGE_H
#define ALERT_PAGE_H

#include "GalleryPage.h"


class BOptionPopUp;
class BTextControl;


class AlertPage : public GalleryPage {
public:
								AlertPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BOptionPopUp*		fType;
			BOptionPopUp*		fButtons;
			BTextControl*		fText;
};

#endif	// ALERT_PAGE_H
