# BListView

Category: Collections · [Back to index](../index.md)

## Purpose

A scrolling list of BListItem objects (usually BStringItem), with single or multiple selection.

## Header and library

- Header: `<ListView.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BListView(const char* name, list_view_type type = B_SINGLE_SELECTION_LIST, uint32 flags = B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE)`
- `BListView(list_view_type type = B_SINGLE_SELECTION_LIST)`
- `BListView(BRect frame, const char* name, list_view_type type = ..., uint32 resizeMask = B_FOLLOW_LEFT_TOP, uint32 flags = ...)`

## Key methods

- AddItem(BListItem*), AddItem(BListItem*, int32), AddList(BList*), RemoveItem(int32), MakeEmpty().
- ItemAt(int32), CountItems(), IndexOf(BListItem*).
- CurrentSelection(int32 index = 0), Select(int32, bool extend), DeselectAll(), ScrollToSelection().
- SetSelectionMessage(BMessage*), SetInvocationMessage(BMessage*).
- SetListType(list_view_type), SortItems(int (*)(const void*, const void*)).

## Messages

Sends its selection message when the selection changes and its invocation message on double-click or Enter. Both carry `index` fields for the selected items.

## Example

```cpp
BListView* list = new BListView("fruits");
list->AddItem(new BStringItem("Apple"));
list->AddItem(new BStringItem("Banana"));
list->SetSelectionMessage(new BMessage(MSG_SELECTED));
BScrollView* scroll = new BScrollView("scroll", list, 0, false, true);

// The list does not own its items:
for (int32 i = list->CountItems() - 1; i >= 0; i--)
	delete list->RemoveItem(i);
```

The gallery's own sample is in `src/pages/ListViewPage.cpp`.

## Haiku Human Interface Guidelines notes

- Put lists in a BScrollView, even if they are short today.
- Double-click (invocation) should do the obvious default action for the item.
- Remember that the list does not delete its items.

## Reference

- The Haiku Book: [BListView](https://www.haiku-os.org/docs/api/classBListView.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
