# BSplitView

Category: Layout · [Back to index](../index.md)

## Purpose

Lays out children in a row or column with draggable splitters between them. Items can be made collapsible.

## Header and library

- Header: `<SplitView.h>` (`<LayoutBuilder.h>`)
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BSplitView(orientation orientation = B_HORIZONTAL, float spacing = B_USE_DEFAULT_SPACING)`
- `BLayoutBuilder::Split<>(BSplitView*) or Group::AddSplit(orientation, spacing, weight)`

## Key methods

- AddChild(BView*, float weight), AddChild(BLayoutItem*, float weight).
- SetOrientation(orientation), SetSplitterSize(float), SetSpacing(float), SetInsets(...).
- SetItemWeight(int32, float, bool invalidateLayout), ItemWeight().
- SetCollapsible(bool) / SetCollapsible(int32, bool), SetItemCollapsed(int32, bool), IsItemCollapsed(int32).

## Messages

None.

## Example

```cpp
BSplitView* split;
BLayoutBuilder::Group<>(this, B_VERTICAL)
	.AddSplit(B_HORIZONTAL)
		.GetSplitView(&split)
		.Add(sidebar, 0.25f)
		.Add(content, 0.75f)
	.End();
split->SetCollapsible(0, true);
```

The gallery's own sample is in `src/pages/SplitViewPage.cpp`.

## Haiku Human Interface Guidelines notes

- Give panes sensible minimum sizes so they cannot be dragged into uselessness.
- Remember the user's split position in your settings.

## Reference

- The Haiku Book: [BSplitView](https://www.haiku-os.org/docs/api/classBSplitView.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
