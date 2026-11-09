# BMenuBar

Category: Menus & selection · [Back to index](../index.md)

## Purpose

The bar of menus at the top of a window. Each entry is a BMenu containing BMenuItem objects, separators (BSeparatorItem) and submenus. This page also covers BMenu and BMenuItem.

## Header and library

- Header: `<MenuBar.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BMenuBar(const char* name, menu_layout layout = B_ITEMS_IN_ROW, uint32 flags = B_WILL_DRAW | B_FRAME_EVENTS)`
- `BMenu(const char* name, menu_layout layout = B_ITEMS_IN_COLUMN)`
- `BMenuItem(const char* label, BMessage* message, char shortcut = 0, uint32 modifiers = 0)`
- `BMenuItem(BMenu* submenu, BMessage* message = NULL)`

## Key methods

- BMenu::AddItem(BMenuItem*), AddItem(BMenu*), AddSeparatorItem(), RemoveItem(), ItemAt(), CountItems().
- BMenu::SetRadioMode(bool), SetLabelFromMarked(bool), FindMarked(), SetEnabled(bool), SetTargetForItems(BHandler*).
- BMenuItem::SetMarked(bool), SetEnabled(bool), SetShortcut(char, uint32), SetLabel(), SetTarget().
- BLayoutBuilder::Menu<> — AddMenu(), AddItem(label, what, shortcut), AddSeparator(), End().
- BWindow::SetKeyMenuBar(BMenuBar*) — choose which menu bar gets keyboard access.

## Messages

Each BMenuItem sends its own message when chosen, with `when`, `source` (the item) and `index` fields. Items without a target send to the window.

## Example

```cpp
BMenuBar* menuBar = new BMenuBar("menuBar");
BLayoutBuilder::Menu<>(menuBar)
	.AddMenu("File")
		.AddItem("Open" B_UTF8_ELLIPSIS, MSG_OPEN, 'O')
		.AddSeparator()
		.AddItem("Quit", B_QUIT_REQUESTED, 'Q')
	.End();

BLayoutBuilder::Group<>(window, B_VERTICAL, 0)
	.Add(menuBar)
	.Add(content);
```

The gallery's own sample is in `src/pages/MenuBarPage.cpp`.

## Haiku Human Interface Guidelines notes

- Use the standard menu order: File (or app name), Edit, View, ..., Help.
- Give common commands the standard shortcuts (Alt/Command+O, S, Q, C, V, X, Z).
- Disable items that do not apply rather than hiding them, so menus keep a stable shape.
- Use an ellipsis for items that open a window or dialog before acting.

## Reference

- The Haiku Book: [BMenuBar](https://www.haiku-os.org/docs/api/classBMenuBar.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
