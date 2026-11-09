# BAlert

Category: Status & info · [Back to index](../index.md)

## Purpose

A small modal window with an icon, a message and up to three buttons. It deletes itself when closed.

## Header and library

- Header: `<Alert.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BAlert(const char* title, const char* text, const char* button1, const char* button2 = NULL, const char* button3 = NULL, button_width width = B_WIDTH_AS_USUAL, alert_type type = B_INFO_ALERT)`
- `BAlert(const char* title, const char* text, const char* button1, const char* button2, const char* button3, button_width width, button_spacing spacing, alert_type type = B_INFO_ALERT)`

## Key methods

- Go() — synchronous; blocks and returns the index of the pressed button. Do not call it from a window's thread.
- Go(BInvoker* invoker) — asynchronous; the invoker's message arrives later with an int32 `which`. Go(NULL) just shows the alert.
- SetShortcut(int32 index, char key) — e.g. B_ESCAPE for Cancel.
- SetType(alert_type) — B_INFO_ALERT, B_IDEA_ALERT, B_WARNING_ALERT, B_STOP_ALERT, B_EMPTY_ALERT.
- SetText(const char*), SetIcon(BBitmap*), SetButtonSpacing(), SetButtonWidth().

## Messages

With Go(BInvoker*), the invoker's message with an int32 `which` field (0, 1 or 2, counting from the left).

## Example

```cpp
BAlert* alert = new BAlert("Delete", "Delete the selected files?",
	"Cancel", "Delete", NULL, B_WIDTH_AS_USUAL, B_WARNING_ALERT);
alert->SetShortcut(0, B_ESCAPE);
alert->Go(new BInvoker(new BMessage(MSG_DELETE_CONFIRMED), this));
```

The gallery's own sample is in `src/pages/AlertPage.cpp`.

## Haiku Human Interface Guidelines notes

- Buttons go from least to most committing, left to right; the rightmost is the default.
- Use verbs on buttons ("Delete", "Don't save") so the alert can be answered without reading the text.
- Use B_WARNING_ALERT for destructive confirmations and B_STOP_ALERT for errors.
- Prefer undo over confirmation alerts where possible.

## Reference

- The Haiku Book: [BAlert](https://www.haiku-os.org/docs/api/classBAlert.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
