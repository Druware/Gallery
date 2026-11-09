# BTextControl

Category: Text · [Back to index](../index.md)

## Purpose

A labelled single-line text field. The usual control for short text input: names, numbers, paths.

## Header and library

- Header: `<TextControl.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BTextControl(const char* name, const char* label, const char* initialText, BMessage* message, uint32 flags = B_WILL_DRAW | B_NAVIGABLE)`
- `BTextControl(const char* label, const char* initialText, BMessage* message)`
- `BTextControl(BRect frame, const char* name, const char* label, const char* initialText, BMessage* message, ...)`

## Key methods

- SetText(const char*) / Text() / TextLength().
- SetModificationMessage(BMessage*) — sent after every edit.
- MarkAsInvalid(bool) — draw the field in an error state.
- TextView() — the embedded BTextView, e.g. TextView()->HideTyping(true) for passwords or DisallowChar() for numeric input.
- SetAlignment(alignment label, alignment text), SetDivider(float).
- CreateLabelLayoutItem() / CreateTextViewLayoutItem() — used by BLayoutBuilder::Grid::AddTextControl().

## Messages

Sends its message when the user presses Enter, or when the field loses focus after its text changed. Sends its modification message after each change.

## Example

```cpp
BTextControl* name = new BTextControl("name", "Name:", "",
	new BMessage(MSG_NAME));
name->SetModificationMessage(new BMessage(MSG_NAME_TYPED));

BLayoutBuilder::Grid<>(this)
	.AddTextControl(name, 0, 0)
	.AddTextControl(email, 0, 1);
```

The gallery's own sample is in `src/pages/TextControlPage.cpp`.

## Haiku Human Interface Guidelines notes

- Line up the labels of stacked fields with a grid (AddTextControl()).
- Validate as the user types and use MarkAsInvalid() rather than an alert when possible.
- Use BTextView for more than one line of text.

## Reference

- The Haiku Book: [BTextControl](https://www.haiku-os.org/docs/api/classBTextControl.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
