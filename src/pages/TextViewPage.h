/*
 * Haiku Gallery - BTextView page.
 */
#ifndef TEXT_VIEW_PAGE_H
#define TEXT_VIEW_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BTextView;


class TextViewPage : public GalleryPage {
public:
								TextViewPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BTextView*			fTextView;
			BCheckBox*			fEditable;
			BCheckBox*			fSelectable;
			BCheckBox*			fWordWrap;
};

#endif	// TEXT_VIEW_PAGE_H
