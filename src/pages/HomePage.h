/*
 * Haiku Gallery - the welcome page with a button for every control.
 */
#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include "GalleryPage.h"

#include <vector>


class HomePage : public GalleryPage {
public:
								// controlPages[i] belongs to PageAt(i) of
								// the registry and is page index i + 1.
								HomePage(
									const std::vector<GalleryPage*>&
										controlPages);

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	const char*			BookClass() const;

	virtual	void				Build();

protected:
	virtual	BView*				CreateSample();

private:
			std::vector<GalleryPage*> fControlPages;
};

#endif	// HOME_PAGE_H
