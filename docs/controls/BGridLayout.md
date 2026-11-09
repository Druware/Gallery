# BGridLayout

Category: Layout · [Back to index](../index.md)

## Purpose

Places items in rows and columns; items can span several cells. The natural layout for forms with aligned labels.

## Header and library

- Header: `<GridLayout.h>` (`<GridView.h>`, `<LayoutBuilder.h>`)
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BGridLayout(float horizontal = B_USE_DEFAULT_SPACING, float vertical = B_USE_DEFAULT_SPACING)`
- `BGridView(float horizontal = B_USE_DEFAULT_SPACING, float vertical = B_USE_DEFAULT_SPACING)`
- `BLayoutBuilder::Grid<>(BView* or BWindow* target, float horizontal, float vertical)`

## Key methods

- AddView(BView*, int32 column, int32 row, int32 columnCount = 1, int32 rowCount = 1).
- SetHorizontalSpacing(float), SetVerticalSpacing(float), SetSpacing(float, float).
- SetColumnWeight(int32, float), SetRowWeight(int32, float), SetMinColumnWidth(), SetMaxColumnWidth().
- Builder: AddTextControl(BTextControl*, column, row), AddMenuField(BMenuField*, column, row) — label and field in adjacent columns.

## Messages

None.

## Example

```cpp
BLayoutBuilder::Grid<>(this)
	.SetInsets(B_USE_WINDOW_INSETS)
	.AddTextControl(nameField, 0, 0)
	.AddTextControl(emailField, 0, 1)
	.AddMenuField(roleField, 0, 2)
	.Add(okButton, 1, 3);
```

The gallery's own sample is in `src/pages/GridLayoutPage.cpp`.

## Haiku Human Interface Guidelines notes

- Right-align labels next to their fields (the default with AddTextControl()).
- Let the field column take the extra width with SetColumnWeight().

## Reference

- The Haiku Book: [BGridLayout](https://www.haiku-os.org/docs/api/classBGridLayout.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
