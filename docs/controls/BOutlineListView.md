# BOutlineListView

Category: Collections · [Back to index](../index.md)

## Purpose

A BListView whose items form a tree. Each item has an outline level; items with children show a disclosure triangle and can be expanded or collapsed.

## Header and library

- Header: `<OutlineListView.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BOutlineListView(const char* name, list_view_type type = B_SINGLE_SELECTION_LIST, uint32 flags = B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE)`
- `BOutlineListView(BRect frame, const char* name, list_view_type type = ..., uint32 resizingMode = B_FOLLOW_LEFT_TOP, uint32 flags = ...)`

## Key methods

- AddItem(BListItem*) — items carry their own OutlineLevel(); AddUnder(BListItem*, BListItem* superItem).
- Expand(BListItem*), Collapse(BListItem*), IsExpanded(int32 fullListIndex).
- Superitem(const BListItem*), CountItemsUnder(BListItem*, bool oneLevelOnly), ItemUnderAt(...).
- FullListItemAt(), FullListCountItems(), FullListIndexOf() — include hidden children; ItemAt()/CountItems() see only visible rows.
- FullListSortItems(), SortItemsUnder().

## Messages

The same selection and invocation messages as BListView.

## Example

```cpp
BOutlineListView* tree = new BOutlineListView("tree");
BStringItem* animals = new BStringItem("Animals");
tree->AddItem(animals);
tree->AddUnder(new BStringItem("Cat"), animals);
tree->AddUnder(new BStringItem("Dog"), animals);
tree->Collapse(animals);
```

The gallery's own sample is in `src/pages/OutlineListViewPage.cpp`.

## Haiku Human Interface Guidelines notes

- Use it when items naturally group into categories, like this gallery's navigation list.
- Keep trees shallow; two or three levels are easy to scan.
- Delete all items, including collapsed ones, via the FullList functions.

## Reference

- The Haiku Book: [BOutlineListView](https://www.haiku-os.org/docs/api/classBOutlineListView.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
