# BStringView

Category: Text · [Back to index](../index.md)

## Purpose

Draws one line of static text. Used for labels, headings and short status messages. It is not editable and sends no messages.

## Header and library

- Header: `<StringView.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BStringView(const char* name, const char* text, uint32 flags = B_WILL_DRAW)`
- `BStringView(BRect frame, const char* name, const char* text, uint32 resizingMode = B_FOLLOW_LEFT_TOP, uint32 flags = B_WILL_DRAW)`

## Key methods

- SetText(const char*) / Text().
- SetAlignment(alignment) — B_ALIGN_LEFT, B_ALIGN_CENTER, B_ALIGN_RIGHT.
- SetTruncation(uint32) — B_TRUNCATE_END, B_TRUNCATE_BEGINNING, B_TRUNCATE_MIDDLE, B_TRUNCATE_SMART.
- SetFont(const BFont*, uint32 mask) — e.g. be_bold_font for headings.

## Messages

None.

## Example

```cpp
BStringView* status = new BStringView("status", "Ready");
status->SetTruncation(B_TRUNCATE_MIDDLE);
// Allow it to shrink below the text width so truncation can happen:
status->SetExplicitMinSize(BSize(50, B_SIZE_UNSET));
status->SetText("Copying 12 files" B_UTF8_ELLIPSIS);
```

The gallery's own sample is in `src/pages/StringViewPage.cpp`.

## Haiku Human Interface Guidelines notes

- Use the system fonts (be_plain_font, be_bold_font) so text follows the user's settings.
- For multi-line or selectable text, use a read-only BTextView instead.
- End labels in front of controls with a colon ("Name:").

## Reference

- The Haiku Book: [BStringView](https://www.haiku-os.org/docs/api/classBStringView.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
