# BGroupLayout

Category: Layout · [Back to index](../index.md)

## Purpose

Arranges items in one row or one column, with spacing between items, insets around them and per-item weights. BGroupView is a view with a BGroupLayout set; BLayoutBuilder::Group builds both.

## Header and library

- Header: `<GroupLayout.h>` (`<GroupView.h>`, `<LayoutBuilder.h>`)
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BGroupLayout(orientation orientation, float spacing = B_USE_DEFAULT_SPACING)`
- `BGroupView(orientation orientation = B_HORIZONTAL, float spacing = B_USE_DEFAULT_SPACING)`
- `BLayoutBuilder::Group<>(BView* or BWindow* target, orientation, float spacing)`

## Key methods

- AddView(BView*, float weight), AddItem(BLayoutItem*, float weight).
- SetOrientation(orientation), SetSpacing(float), SetInsets(float ...).
- SetItemWeight(int32 index, float weight) / ItemWeight().
- Builder: Add(), AddGroup(), AddGrid(), AddSplit(), AddCards(), AddGlue(), AddStrut(), SetInsets(), End().

## Messages

None.

## Example

```cpp
BLayoutBuilder::Group<>(this, B_VERTICAL)
	.SetInsets(B_USE_WINDOW_INSETS)
	.Add(textView)
	.AddGroup(B_HORIZONTAL)
		.AddGlue()
		.Add(cancelButton)
		.Add(okButton)
	.End();
```

The gallery's own sample is in `src/pages/GroupLayoutPage.cpp`.

## Haiku Human Interface Guidelines notes

- Use the symbolic spacing constants (B_USE_DEFAULT_SPACING, B_USE_WINDOW_INSETS, B_USE_SMALL_SPACING) so layouts scale with the font size.
- Never hard-code pixel positions; let the layout compute them.
- Use B_AUTO_UPDATE_SIZE_LIMITS on windows so they cannot be made too small.

## Reference

- The Haiku Book: [BGroupLayout](https://www.haiku-os.org/docs/api/classBGroupLayout.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
