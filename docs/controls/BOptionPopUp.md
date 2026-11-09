# BOptionPopUp

Category: Menus & selection · [Back to index](../index.md)

## Purpose

A BControl (via BOptionControl) wrapping a BMenuField. Each option pairs a name with an int32 value; Value() returns the selected option's value.

## Header and library

- Header: `<OptionPopUp.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BOptionPopUp(const char* name, const char* label, BMessage* message, uint32 flags = B_WILL_DRAW)`
- `BOptionPopUp(BRect frame, const char* name, const char* label, BMessage* message, uint32 resizeMask = B_FOLLOW_LEFT_TOP, uint32 flags = B_WILL_DRAW)`

## Key methods

- AddOption(const char* name, int32 value), AddOptionAt(name, value, index), RemoveOptionAt(int32), CountOptions().
- SetValue(int32) / Value() — select by value.
- SelectOptionFor(int32 value) / SelectOptionFor(const char* name).
- SelectedOption(const char** name, int32* value) — returns the selected index.
- MenuField() — the wrapped BMenuField.

## Messages

Sends its own message when the user picks an option.

## Example

```cpp
BOptionPopUp* quality = new BOptionPopUp("quality", "Quality:",
	new BMessage(MSG_QUALITY));
quality->AddOption("Low", 25);
quality->AddOption("Medium", 50);
quality->AddOption("High", 90);
quality->SetValue(50);
```

The gallery's own sample is in `src/pages/OptionPopUpPage.cpp`.

## Haiku Human Interface Guidelines notes

- The same guidelines as BMenuField apply.
- Use meaningful values so the code that reads Value() does not need a lookup table.

## Reference

- The Haiku Book: [BOptionPopUp](https://www.haiku-os.org/docs/api/classBOptionPopUp.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
