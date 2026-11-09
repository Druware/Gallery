# BCardLayout

Category: Layout · [Back to index](../index.md)

## Purpose

Stacks items like cards and shows only one at a time. BCardView is a view with a BCardLayout set.

## Header and library

- Header: `<CardLayout.h>` (`<CardView.h>`, `<LayoutBuilder.h>`)
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BCardLayout()`
- `BCardView(const char* name)`
- `BLayoutBuilder::Cards<>() or Group::AddCards()`

## Key methods

- AddView(BView*), AddItem(BLayoutItem*) — inherited from BLayout.
- SetVisibleItem(int32) / SetVisibleItem(BLayoutItem*), VisibleIndex(), VisibleItem().
- BCardView::CardLayout() — the layout of a card view.

## Messages

None.

## Example

```cpp
BCardView* cards = new BCardView("pages");
cards->CardLayout()->AddView(generalPage);
cards->CardLayout()->AddView(networkPage);
cards->CardLayout()->SetVisibleItem((int32)0);
```

The gallery's own sample is in `src/pages/CardLayoutPage.cpp`.

## Haiku Human Interface Guidelines notes

- Pair a card layout with a visible selector (list, tabs, buttons) so users know other cards exist.
- The layout's minimum size is that of the largest card; keep cards similar in size.

## Reference

- The Haiku Book: [BCardLayout](https://www.haiku-os.org/docs/api/classBCardLayout.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
