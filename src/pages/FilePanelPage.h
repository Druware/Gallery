/*
 * Haiku Gallery - BFilePanel page.
 */
#ifndef FILE_PANEL_PAGE_H
#define FILE_PANEL_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BFilePanel;


class FilePanelPage : public GalleryPage {
public:
								FilePanelPage();
	virtual						~FilePanelPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			void				_ShowPanel(bool save);

			BFilePanel*			fPanel;
			BCheckBox*			fMultiple;
			BCheckBox*			fDirectories;
};

#endif	// FILE_PANEL_PAGE_H
