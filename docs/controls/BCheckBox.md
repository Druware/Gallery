# BCheckBox

Category: Basic input · [Back to index](../index.md)

## Purpose

An on/off control with a label, used for independent options. It also supports a third, mixed state (B_CONTROL_PARTIALLY_ON) for a parent option whose children are partly selected.

## Header and library

- Header: `<CheckBox.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BCheckBox(const char* name, const char* label, BMessage* message, uint32 flags = B_WILL_DRAW | B_NAVIGABLE)`
- `BCheckBox(const char* label, BMessage* message = NULL)`
- `BCheckBox(BRect frame, const char* name, const char* label, BMessage* message, uint32 resizingMode = B_FOLLOW_LEFT_TOP, uint32 flags = ...)`

## Key methods

- SetValue(int32) / Value() — B_CONTROL_OFF, B_CONTROL_ON or B_CONTROL_PARTIALLY_ON.
- SetPartialStateToOff(bool) — whether clicking a mixed box turns it off (default: on).
- SetLabel(const char*), SetEnabled(bool) — from BControl.
- SetIcon(const BBitmap*, uint32) — optional icon.

## Messages

Sends its message each time the user toggles it; read the new state with Value() or the `be:value` field.

## Example

```cpp
BCheckBox* autosave = new BCheckBox("autosave", "Save automatically",
	new BMessage(MSG_AUTOSAVE));
autosave->SetValue(settings.autosave ? B_CONTROL_ON : B_CONTROL_OFF);

// In MessageReceived():
case MSG_AUTOSAVE:
	settings.autosave = autosave->Value() == B_CONTROL_ON;
	break;
```

The gallery's own sample is in `src/pages/CheckBoxPage.cpp`.

## Haiku Human Interface Guidelines notes

- Phrase the label so that "checked" means the statement is true ("Show hidden files").
- Use check boxes for independent options; use radio buttons when exactly one choice applies.
- Changes made with check boxes in preference windows should usually take effect immediately.

## Reference

- The Haiku Book: [BCheckBox](https://www.haiku-os.org/docs/api/classBCheckBox.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
