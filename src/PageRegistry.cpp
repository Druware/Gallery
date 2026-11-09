/*
 * Haiku Gallery - the list of all control pages.
 */
#include "PageRegistry.h"

#include "AlertPage.h"
#include "BoxPage.h"
#include "ButtonPage.h"
#include "CardLayoutPage.h"
#include "CheckBoxPage.h"
#include "ColorControlPage.h"
#include "FilePanelPage.h"
#include "GridLayoutPage.h"
#include "GroupLayoutPage.h"
#include "ListViewPage.h"
#include "MenuBarPage.h"
#include "MenuFieldPage.h"
#include "OptionPopUpPage.h"
#include "OutlineListViewPage.h"
#include "PopUpMenuPage.h"
#include "RadioButtonPage.h"
#include "ScrollViewPage.h"
#include "SeparatorViewPage.h"
#include "SliderPage.h"
#include "SplitViewPage.h"
#include "StatusBarPage.h"
#include "StringViewPage.h"
#include "TabViewPage.h"
#include "TextControlPage.h"
#include "TextViewPage.h"
#include "ToolTipPage.h"


template<class T>
static GalleryPage*
Create()
{
	return new T();
}


// Category names appear in the navigation list in the order they first
// appear here.
static const PageEntry kPages[] = {
	{ "Basic input",		&Create<ButtonPage> },
	{ "Basic input",		&Create<CheckBoxPage> },
	{ "Basic input",		&Create<RadioButtonPage> },
	{ "Basic input",		&Create<SliderPage> },
	{ "Text",				&Create<StringViewPage> },
	{ "Text",				&Create<TextControlPage> },
	{ "Text",				&Create<TextViewPage> },
	{ "Collections",		&Create<ListViewPage> },
	{ "Collections",		&Create<OutlineListViewPage> },
	{ "Menus & selection",	&Create<MenuBarPage> },
	{ "Menus & selection",	&Create<PopUpMenuPage> },
	{ "Menus & selection",	&Create<MenuFieldPage> },
	{ "Menus & selection",	&Create<OptionPopUpPage> },
	{ "Status & info",		&Create<StatusBarPage> },
	{ "Status & info",		&Create<AlertPage> },
	{ "Status & info",		&Create<ToolTipPage> },
	{ "Layout",				&Create<GroupLayoutPage> },
	{ "Layout",				&Create<GridLayoutPage> },
	{ "Layout",				&Create<SplitViewPage> },
	{ "Layout",				&Create<CardLayoutPage> },
	{ "Layout",				&Create<TabViewPage> },
	{ "Layout",				&Create<BoxPage> },
	{ "Layout",				&Create<ScrollViewPage> },
	{ "Layout",				&Create<SeparatorViewPage> },
	{ "Pickers",			&Create<ColorControlPage> },
	{ "Pickers",			&Create<FilePanelPage> },
};


int32
PageCount()
{
	return sizeof(kPages) / sizeof(kPages[0]);
}


const PageEntry&
PageAt(int32 index)
{
	return kPages[index];
}
