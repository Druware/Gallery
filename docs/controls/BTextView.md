# BTextView

Category: Text · [Back to index](../index.md)

## Purpose

A multi-line text editing view with optional styled text, word wrapping, undo and clipboard support. It is also the engine inside BTextControl. Wrap it in a BScrollView for scroll bars.

## Header and library

- Header: `<TextView.h>`
- Library: `libbe.so` (makefile-engine: `LIBS = be`)

## Key constructors

- `BTextView(const char* name, uint32 flags = B_WILL_DRAW | B_PULSE_NEEDED)`
- `BTextView(const char* name, const BFont* initialFont, const rgb_color* initialColor, uint32 flags)`
- `BTextView(BRect frame, const char* name, BRect textRect, uint32 resizeMask, uint32 flags = ...)` (frame-based)

## Key methods

- SetText(const char*), Insert(const char*), Delete(), Text(), TextLength(), CountLines().
- MakeEditable(bool), MakeSelectable(bool), SetWordWrap(bool), SetStylable(bool).
- Select(int32, int32), SelectAll(), GetSelection(int32*, int32*).
- SetFontAndColor(const BFont*, uint32 mode, const rgb_color*).
- Copy(BClipboard*), Cut(), Paste(), Undo().
- HideTyping(bool), DisallowChar(uint32), SetMaxBytes(int32).
- Protected InsertText() / DeleteText() — override to observe edits.

## Messages

None of its own. To react to edits, subclass and override InsertText() and DeleteText().

## Example

```cpp
BTextView* notes = new BTextView("notes");
notes->SetWordWrap(true);
notes->SetText("Type here");
BScrollView* scroll = new BScrollView("scroll", notes, 0, false, true);
```

The gallery's own sample is in `src/pages/TextViewPage.cpp`.

## Haiku Human Interface Guidelines notes

- Put editable text in a BScrollView with a border so the editable area is obvious.
- Read-only text that should be copyable (like this gallery's source boxes) is a BTextView with MakeEditable(false).
- Call AdoptSystemColors() so the view follows the document colors the user has chosen.

## Reference

- The Haiku Book: [BTextView](https://www.haiku-os.org/docs/api/classBTextView.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
