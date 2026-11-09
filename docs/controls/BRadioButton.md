# BRadioButton

Category: Basic input · [Back to index](../index.md)

## Purpose

A control for choosing exactly one option from a small set. Radio buttons that share the same parent view are mutually exclusive: turning one on turns its siblings off.

## Header and library

- Header: `<RadioButton.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BRadioButton(const char* name, const char* label, BMessage* message, uint32 flags = B_WILL_DRAW | B_NAVIGABLE)`
- `BRadioButton(const char* label, BMessage* message)`
- `BRadioButton(BRect frame, const char* name, const char* label, BMessage* message, uint32 resizingMode = B_FOLLOW_LEFT_TOP, uint32 flags = ...)`

## Key methods

- SetValue(B_CONTROL_ON) — select this button (siblings are turned off).
- Value() — B_CONTROL_ON for the selected button.
- SetEnabled(bool), SetLabel(const char*) — from BControl.

## Messages

Sends its message when the user selects it. Add a field (for example an `index`) to each button's message to tell them apart.

## Example

```cpp
BGroupLayout* group = BLayoutBuilder::Group<>(B_VERTICAL);
const char* sizes[] = { "Small", "Medium", "Large" };
for (int32 i = 0; i < 3; i++) {
	BMessage* message = new BMessage(MSG_SIZE);
	message->AddInt32("index", i);
	group->AddView(new BRadioButton(sizes[i], sizes[i], message));
}
```

The gallery's own sample is in `src/pages/RadioButtonPage.cpp`.

## Haiku Human Interface Guidelines notes

- Always have one button selected; give the set a sensible default.
- Keep each set in its own parent view (BBox or group view) so sets don't interfere.
- For more than about five choices, consider a BMenuField or BOptionPopUp instead.

## Reference

- The Haiku Book: [BRadioButton](https://www.haiku-os.org/docs/api/classBRadioButton.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
