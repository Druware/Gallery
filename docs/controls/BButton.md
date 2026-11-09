# BButton

Category: Basic input · [Back to index](../index.md)

## Purpose

A push button. Clicking it (or pressing Space/Enter while it has focus) sends its BMessage to its target. A button can also act as a toggle (stays pressed) or as a pop-up trigger.

## Header and library

- Header: `<Button.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BButton(const char* name, const char* label, BMessage* message, uint32 flags = B_WILL_DRAW | B_NAVIGABLE | B_FULL_UPDATE_ON_RESIZE)`
- `BButton(const char* label, BMessage* message = NULL)`
- `BButton(BRect frame, const char* name, const char* label, BMessage* message, uint32 resizingMode = B_FOLLOW_LEFT_TOP, uint32 flags = ...)` (frame-based, pre-layout code)

## Key methods

- SetLabel(const char*) / Label() — change the text.
- SetEnabled(bool) / IsEnabled() — inherited from BControl.
- SetBehavior(BButton::B_TOGGLE_BEHAVIOR) — make it a toggle; Value() is then B_CONTROL_ON or B_CONTROL_OFF.
- MakeDefault(bool) — the window's default button, triggered by Enter anywhere in the window.
- SetIcon(const BBitmap*, uint32 flags) — show an icon next to (or instead of) the label.
- SetTarget(BHandler*) / SetMessage(BMessage*) — inherited from BInvoker.

## Messages

Sends its own message (set in the constructor or with SetMessage()). BControl::Invoke() adds `when` (int64), `source` (pointer) and `be:value` (int32) fields.

## Example

```cpp
BButton* button = new BButton("ok", "OK", new BMessage(MSG_OK));
button->SetToolTip("Accept the changes");

BLayoutBuilder::Group<>(this, B_HORIZONTAL)
	.AddGlue()
	.Add(new BButton("cancel", "Cancel", new BMessage(B_QUIT_REQUESTED)))
	.Add(button);

window->SetDefaultButton(button);
```

The gallery's own sample is in `src/pages/ButtonPage.cpp`.

## Haiku Human Interface Guidelines notes

- Label buttons with a verb that says what will happen ("Save", "Delete"), not "OK" when a verb fits.
- Add an ellipsis (B_UTF8_ELLIPSIS) when the button opens a further dialog before acting.
- Place the default (rightmost) button at the bottom right of a dialog, with Cancel to its left.
- Let the layout size buttons; do not hard-code widths.

## Reference

- The Haiku Book: [BButton](https://www.haiku-os.org/docs/api/classBButton.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
