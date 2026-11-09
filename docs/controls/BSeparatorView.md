# BSeparatorView

Category: Layout · [Back to index](../index.md)

## Purpose

A horizontal or vertical line that divides parts of a layout, optionally with a label set into the line.

## Header and library

- Header: `<SeparatorView.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BSeparatorView(orientation orientation, border_style border = B_PLAIN_BORDER)`
- `BSeparatorView(const char* name, const char* label, orientation orientation = B_HORIZONTAL, border_style border = B_FANCY_BORDER, const BAlignment& alignment = ...)`
- `BSeparatorView(const char* label = NULL, orientation = B_HORIZONTAL, border_style = B_FANCY_BORDER, const BAlignment& = ...)`

## Key methods

- SetLabel(const char*) / SetLabel(BView*, bool deletePrevious).
- SetOrientation(orientation), SetAlignment(const BAlignment&), SetBorderStyle(border_style).

## Messages

None.

## Example

```cpp
BLayoutBuilder::Group<>(this, B_VERTICAL)
	.Add(new BSeparatorView("Appearance", B_HORIZONTAL, B_FANCY_BORDER,
		BAlignment(B_ALIGN_LEFT, B_ALIGN_VERTICAL_CENTER)))
	.Add(appearanceControls)
	.Add(new BSeparatorView(B_HORIZONTAL))
	.Add(otherControls);
```

The gallery's own sample is in `src/pages/SeparatorViewPage.cpp`.

## Haiku Human Interface Guidelines notes

- Use a labelled separator instead of a box when a section only needs a heading.
- Do not separate every control; whitespace from the layout is often enough.

## Reference

- The Haiku Book: [BSeparatorView](https://www.haiku-os.org/docs/api/classBSeparatorView.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
