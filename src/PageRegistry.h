/*
 * Haiku Gallery - the list of all control pages.
 *
 * To add a control: write a GalleryPage subclass and add one line to
 * kPages in PageRegistry.cpp. Navigation, search and the home page pick
 * it up automatically.
 */
#ifndef PAGE_REGISTRY_H
#define PAGE_REGISTRY_H

#include <SupportDefs.h>


class GalleryPage;


struct PageEntry {
	const char*		category;
	GalleryPage*	(*create)();
};


int32				PageCount();
const PageEntry&	PageAt(int32 index);

#endif	// PAGE_REGISTRY_H
