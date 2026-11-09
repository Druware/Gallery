/*
 * Haiku Gallery - abstract base class for one gallery page.
 *
 * A page shows: a title, a one-paragraph description, a live sample
 * (CreateSample), an optional options panel that changes the sample at
 * run time (CreateOptions), a line reporting the last message received,
 * and a read-only, copyable source snippet.
 *
 * Controls created by a page keep their default target (the window).
 * MainWindow forwards every message it does not handle itself to
 * HandleMessage(), so subclasses simply switch on the codes from
 * Messages.h and return true for the ones they consume.
 */
#ifndef GALLERY_PAGE_H
#define GALLERY_PAGE_H

#include <View.h>


class BStringView;
class BTextView;


class GalleryPage : public BView {
public:
								GalleryPage(const char* name);
	virtual						~GalleryPage();

	// Short title shown in the navigation list, e.g. "BButton".
	virtual	const char*			Title() const = 0;
	// One paragraph shown under the title.
	virtual	const char*			Description() const = 0;
	// Source code shown in the snippet box.
	virtual	const char*			SourceSnippet() const = 0;
	// Class name used for the Haiku Book link; NULL for no link.
	virtual	const char*			BookClass() const;

	// Builds the page's views. Called once, right after construction,
	// because the layout depends on the virtual methods above.
	virtual	void				Build();

	// Returns true when the message was meant for this page.
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample() = 0;
	virtual	BView*				CreateOptions();

			void				LogEvent(const char* format, ...)
									__attribute__((format(printf, 2, 3)));

private:
			BStringView*		fEventLine;
			BTextView*			fSourceView;
};

#endif	// GALLERY_PAGE_H
