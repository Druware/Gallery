# BStatusBar

Category: Status & info · [Back to index](../index.md)

## Purpose

A progress bar with labels: a leading label and trailing label above the bar, each followed by optional text.

## Header and library

- Header: `<StatusBar.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BStatusBar(const char* name, const char* label = NULL, const char* trailingLabel = NULL)`
- `BStatusBar(BRect frame, const char* name, const char* label = NULL, const char* trailingLabel = NULL)`

## Key methods

- Update(float delta, const char* text = NULL, const char* trailingText = NULL) — advance the bar.
- Reset(const char* label = NULL, const char* trailingLabel = NULL) — back to zero.
- SetMaxValue(float) / MaxValue(), CurrentValue(), SetTo(float value, ...).
- SetText(), SetTrailingText(), SetBarColor(rgb_color), SetBarHeight(float).

## Messages

None. It accepts B_UPDATE_STATUS_BAR and B_RESET_STATUS_BAR messages, so other threads can drive it with BMessenger.

## Example

```cpp
BStatusBar* progress = new BStatusBar("progress", "Copying", "files");
progress->SetMaxValue(fileCount);

// From any thread, via the window:
BMessage update(B_UPDATE_STATUS_BAR);
update.AddFloat("delta", 1.0f);
BMessenger(progress).SendMessage(&update);
```

The gallery's own sample is in `src/pages/StatusBarPage.cpp`.

## Haiku Human Interface Guidelines notes

- Show progress for operations that take more than a couple of seconds.
- Say what is happening in the label and how far along in the trailing text.
- Do long work in a separate thread so the window stays responsive.

## Reference

- The Haiku Book: [BStatusBar](https://www.haiku-os.org/docs/api/classBStatusBar.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
