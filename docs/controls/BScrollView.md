# BScrollView

Category: Layout · [Back to index](../index.md)

## Purpose

Wraps a target view with horizontal and/or vertical BScrollBar objects and a border.

## Header and library

- Header: `<ScrollView.h>` (`<ScrollBar.h>`)
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BScrollView(const char* name, BView* target, uint32 flags, bool horizontal, bool vertical, border_style border = B_FANCY_BORDER)`
- `BScrollView(const char* name, BView* target, uint32 resizingMode = B_FOLLOW_LEFT_TOP, uint32 flags = 0, bool horizontal = false, bool vertical = false, border_style border = B_FANCY_BORDER)`

## Key methods

- ScrollBar(orientation) — the BScrollBar, for SetRange(), SetProportion(), SetSteps().
- SetBorder(border_style), SetBorders(uint32), SetBorderHighlighted(bool).
- SetTarget(BView*), Target().

## Messages

None. BListView, BOutlineListView and BTextView update their scroll bars themselves; custom views set the range.

## Example

```cpp
BScrollView* scroll = new BScrollView("scroll", listView, 0,
	false, true);   // vertical scroll bar only
```

The gallery's own sample is in `src/pages/ScrollViewPage.cpp`.

## Haiku Human Interface Guidelines notes

- Show scroll bars only on axes that can scroll; text that wraps needs no horizontal bar.
- Use the fancy border for content areas so they read as a separate surface.

## Reference

- The Haiku Book: [BScrollView](https://www.haiku-os.org/docs/api/classBScrollView.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
