# Tooltips

Category: Status & info · [Back to index](../index.md)

## Purpose

Every BView can show a tooltip after the mouse rests over it. A tooltip is a string, or a BToolTip object for custom content.

## Header and library

- Header: `<View.h>` (and `<ToolTip.h>` for BToolTip)
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BView::SetToolTip(const char* text)`
- `BView::SetToolTip(BToolTip* tip)`

## Key methods

- SetToolTip((const char*)NULL) — remove the tooltip.
- ToolTip() — the current BToolTip.
- ShowToolTip(BToolTip*), HideToolTip().
- GetToolTipAt(BPoint, BToolTip**) — override to vary the tooltip by position.

## Messages

None.

## Example

```cpp
BButton* save = new BButton("save", "Save", new BMessage(MSG_SAVE));
save->SetToolTip("Save the document");
```

The gallery's own sample is in `src/pages/ToolTipPage.cpp`.

## Haiku Human Interface Guidelines notes

- Use tooltips to explain, not to label: the control should make sense without one.
- Keep them short; one line is ideal.
- Give icon-only buttons a tooltip naming their action.

## Reference

- The Haiku Book: [BView](https://www.haiku-os.org/docs/api/classBView.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
