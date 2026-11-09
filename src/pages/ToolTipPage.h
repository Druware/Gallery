/*
 * Haiku Gallery - tooltips (BView::SetToolTip) page.
 */
#ifndef TOOL_TIP_PAGE_H
#define TOOL_TIP_PAGE_H

#include "GalleryPage.h"


class BButton;
class BCheckBox;
class BTextControl;


class ToolTipPage : public GalleryPage {
public:
								ToolTipPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	const char*			BookClass() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			void				_Apply();

			BButton*			fButton;
			BTextControl*		fText;
			BCheckBox*			fEnabled;
};

#endif	// TOOL_TIP_PAGE_H
