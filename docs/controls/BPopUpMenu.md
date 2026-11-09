# BPopUpMenu

Category: Menus & selection · [Back to index](../index.md)

## Purpose

A menu that appears on demand, typically as a context menu at the mouse position. It is also the menu type used by BMenuField.

## Header and library

- Header: `<PopUpMenu.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BPopUpMenu(const char* name, bool radioMode = true, bool labelFromMarked = true, menu_layout layout = B_ITEMS_IN_COLUMN)`

## Key methods

- Go(BPoint screenWhere, bool autoInvoke = false, bool keepOpen = false, bool async = false) — show the menu; returns the chosen item when synchronous.
- Go(BPoint, bool, bool, BRect openRect, bool async = false) — with a click-to-open rectangle.
- SetAsyncAutoDestruct(bool) — delete itself after an asynchronous Go().
- Everything from BMenu: AddItem(), AddSeparatorItem(), SetRadioMode() ...

## Messages

With autoInvoke = false nothing is sent; Go() returns the item and you act on it. With autoInvoke = true the item's message is sent to its target as usual.

## Example

```cpp
void
MyView::MouseDown(BPoint where)
{
	BPopUpMenu* menu = new BPopUpMenu("context", false, false);
	menu->AddItem(new BMenuItem("Copy", new BMessage(B_COPY)));
	menu->AddItem(new BMenuItem("Paste", new BMessage(B_PASTE)));
	menu->SetTargetForItems(this);

	ConvertToScreen(&where);
	menu->Go(where, true, true, true);   // async, invokes the item
	menu->SetAsyncAutoDestruct(true);
}
```

The gallery's own sample is in `src/pages/PopUpMenuPage.cpp`.

## Haiku Human Interface Guidelines notes

- Context menus should repeat commands available elsewhere, never offer the only way to do something.
- Keep context menus short and relevant to what was clicked.
- Open them on the secondary mouse button; Haiku users may also expect a click-and-hold.

## Reference

- The Haiku Book: [BPopUpMenu](https://www.haiku-os.org/docs/api/classBPopUpMenu.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
