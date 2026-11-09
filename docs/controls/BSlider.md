# BSlider

Category: Basic input · [Back to index](../index.md)

## Purpose

A control for picking an integer in a range by dragging a thumb along a bar. It supports horizontal and vertical orientation, hash marks, limit labels, two thumb styles and a fill color.

## Header and library

- Header: `<Slider.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BSlider(const char* name, const char* label, BMessage* message, int32 minValue, int32 maxValue, orientation posture, thumb_style thumbType = B_BLOCK_THUMB, uint32 flags = B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS)`
- `BSlider(BRect frame, const char* name, const char* label, BMessage* message, int32 minValue, int32 maxValue, thumb_style thumbType = B_BLOCK_THUMB, ...)`

## Key methods

- SetValue(int32) / Value(); SetLimits(int32, int32) / GetLimits().
- SetModificationMessage(BMessage*) — sent continuously while dragging.
- SetHashMarks(hash_mark_location) and SetHashMarkCount(int32).
- SetLimitLabels(const char* min, const char* max).
- SetOrientation(orientation), SetStyle(thumb_style), SetBarThickness(float).
- UseFillColor(bool, const rgb_color*), SetBarColor(rgb_color).
- SetKeyIncrementValue(int32) — step for arrow keys.
- UpdateText() — override to show a value label (return a string).

## Messages

Sends its message when the user releases the thumb (or changes the value with the keyboard), and its modification message, if set, on every change while dragging.

## Example

```cpp
BSlider* volume = new BSlider("volume", "Volume", new BMessage(MSG_VOLUME),
	0, 100, B_HORIZONTAL);
volume->SetModificationMessage(new BMessage(MSG_VOLUME_DRAG));
volume->SetHashMarks(B_HASH_MARKS_BOTTOM);
volume->SetHashMarkCount(11);
volume->SetLimitLabels("Quiet", "Loud");
```

The gallery's own sample is in `src/pages/SliderPage.cpp`.

## Haiku Human Interface Guidelines notes

- Label the slider and its limits so the user knows what the ends mean.
- Use the modification message for live feedback only if the update is cheap.
- For precise values, pair the slider with a text field.

## Reference

- The Haiku Book: [BSlider](https://www.haiku-os.org/docs/api/classBSlider.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
