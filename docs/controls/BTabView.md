# BTabView

Category: Layout · [Back to index](../index.md)

## Purpose

Shows one of several views, chosen with tabs. Each tab is a BTab that takes its label from its view's name unless you set one.

## Header and library

- Header: `<TabView.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BTabView(const char* name, button_width width = B_WIDTH_FROM_WIDEST, uint32 flags = ...)`
- `BTab(BView* contentsView = NULL)`

## Key methods

- AddTab(BView* target, BTab* tab = NULL), RemoveTab(int32), TabAt(int32), CountTabs().
- Select(int32) / Selection() — override Select() to be notified of changes.
- SetTabSide(BTabView::tab_side) — kTopSide, kBottomSide, kLeftSide, kRightSide.
- SetBorder(border_style), SetTabWidth(button_width), SetTabHeight(float).
- BTab::SetLabel(const char*), SetEnabled(bool).

## Messages

None. Override Select(int32) to observe tab changes.

## Example

```cpp
BTabView* tabs = new BTabView("tabs", B_WIDTH_FROM_LABEL);
BView* general = new BGroupView("General");
BView* network = new BGroupView("Network");
tabs->AddTab(general);
tabs->AddTab(network);
```

The gallery's own sample is in `src/pages/TabViewPage.cpp`.

## Haiku Human Interface Guidelines notes

- Use tabs for a few peer sections of settings; for many sections use a list plus a card layout.
- Keep tab labels short, one or two words.
- Do not nest tab views.

## Reference

- The Haiku Book: [BTabView](https://www.haiku-os.org/docs/api/classBTabView.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
