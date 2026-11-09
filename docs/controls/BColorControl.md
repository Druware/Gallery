# BColorControl

Category: Pickers · [Back to index](../index.md)

## Purpose

Haiku's built-in color picker: red, green and blue ramps with text fields for exact values (a palette of 256 cells on 8-bit screens).

## Header and library

- Header: `<ColorControl.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BColorControl(BPoint start, color_control_layout layout, float cellSize, const char* name, BMessage* message = NULL, bool useOffscreen = false)`

## Key methods

- SetValue(rgb_color) / SetValue(int32), ValueAsColor(), Value().
- SetLayout(color_control_layout) — B_CELLS_4x64, B_CELLS_8x32, B_CELLS_16x16, B_CELLS_32x8, B_CELLS_64x4.
- SetCellSize(float) / CellSize().
- SetEnabled(bool).

## Messages

Sends its message whenever the color changes.

## Example

```cpp
BColorControl* picker = new BColorControl(B_ORIGIN, B_CELLS_32x8, 8.0f,
	"color", new BMessage(MSG_COLOR));
picker->SetValue(make_color(255, 203, 0));

// In MessageReceived():
case MSG_COLOR:
	fColor = picker->ValueAsColor();
	break;
```

The gallery's own sample is in `src/pages/ColorControlPage.cpp`.

## Haiku Human Interface Guidelines notes

- Show a preview of the chosen color next to the control.
- In layouts the BPoint argument is ignored; pass B_ORIGIN.

## Reference

- The Haiku Book: [BColorControl](https://www.haiku-os.org/docs/api/classBColorControl.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
