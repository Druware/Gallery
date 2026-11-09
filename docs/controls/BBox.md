# BBox

Category: Layout · [Back to index](../index.md)

## Purpose

Draws a frame around related controls, with an optional label in the top border. The label can be a string or any view, such as a BCheckBox.

## Header and library

- Header: `<Box.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BBox(const char* name, uint32 flags = B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE_JUMP, border_style border = B_FANCY_BORDER, BView* child = NULL)`
- `BBox(border_style border, BView* child)`

## Key methods

- AddChild(BView*) — give the box one child with its own layout.
- SetLabel(const char*) / SetLabel(BView*) (takes ownership), Label(), LabelView().
- SetBorder(border_style) — B_FANCY_BORDER, B_PLAIN_BORDER, B_NO_BORDER.
- InnerFrame(), TopBorderOffset().

## Messages

None (a label view such as a BCheckBox sends its own message).

## Example

```cpp
BBox* box = new BBox("options");
box->SetLabel("Options");
box->AddChild(BLayoutBuilder::Group<>(B_VERTICAL)
	.SetInsets(B_USE_DEFAULT_SPACING)
	.Add(checkBox1)
	.Add(checkBox2)
	.View());
```

The gallery's own sample is in `src/pages/BoxPage.cpp`.

## Haiku Human Interface Guidelines notes

- Use boxes to group related settings; avoid boxes inside boxes.
- A check box label is a good way to enable or disable a whole group.

## Reference

- The Haiku Book: [BBox](https://www.haiku-os.org/docs/api/classBBox.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
