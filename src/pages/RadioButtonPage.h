/*
 * Haiku Gallery - BRadioButton page.
 */
#ifndef RADIO_BUTTON_PAGE_H
#define RADIO_BUTTON_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BRadioButton;


class RadioButtonPage : public GalleryPage {
public:
								RadioButtonPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
	static	const int32			kChoiceCount = 3;

			BRadioButton*		fChoices[kChoiceCount];
			BCheckBox*			fEnabled;
};

#endif	// RADIO_BUTTON_PAGE_H
