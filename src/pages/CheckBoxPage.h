/*
 * Haiku Gallery - BCheckBox page.
 */
#ifndef CHECK_BOX_PAGE_H
#define CHECK_BOX_PAGE_H

#include "GalleryPage.h"


class BCheckBox;


class CheckBoxPage : public GalleryPage {
public:
								CheckBoxPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			void				_UpdateAll();

	static	const int32			kItemCount = 3;

			BCheckBox*			fAll;
			BCheckBox*			fItems[kItemCount];
			BCheckBox*			fEnabled;
};

#endif	// CHECK_BOX_PAGE_H
