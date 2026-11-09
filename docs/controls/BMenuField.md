# BMenuField

Category: Menus & selection · [Back to index](../index.md)

## Purpose

A label plus a pop-up menu that shows the currently selected item; Haiku's drop-down list.

## Header and library

- Header: `<MenuField.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BMenuField(const char* name, const char* label, BMenu* menu, uint32 flags = B_WILL_DRAW | B_NAVIGABLE)`
- `BMenuField(const char* name, const char* label, BMenu* menu, bool fixedSize, uint32 flags = ...)`
- `BMenuField(const char* label, BMenu* menu, uint32 flags = ...)`

## Key methods

- Menu() — the BMenu (usually a BPopUpMenu); MenuItem() — the item showing the current choice.
- SetLabel(const char*), SetEnabled(bool), SetDivider(float), SetAlignment(alignment).
- CreateLabelLayoutItem() / CreateMenuBarLayoutItem() — used by BLayoutBuilder::Grid::AddMenuField().

## Messages

The field itself sends nothing; each menu item sends its own message when chosen.

## Example

```cpp
BPopUpMenu* menu = new BPopUpMenu("format");
menu->AddItem(new BMenuItem("PNG", new BMessage(MSG_PNG)));
menu->AddItem(new BMenuItem("JPEG", new BMessage(MSG_JPEG)));
menu->ItemAt(0)->SetMarked(true);

BMenuField* format = new BMenuField("format", "Format:", menu);
```

The gallery's own sample is in `src/pages/MenuFieldPage.cpp`.

## Haiku Human Interface Guidelines notes

- Use a radio-mode BPopUpMenu with label-from-marked so the field always shows the current value.
- Align menu fields with text fields using a grid (AddMenuField()).
- If you only need name/value options, BOptionPopUp is less code.

## Reference

- The Haiku Book: [BMenuField](https://www.haiku-os.org/docs/api/classBMenuField.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
