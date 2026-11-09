# BFilePanel

Category: Pickers · [Back to index](../index.md)

## Purpose

The standard Open and Save dialog, provided by Tracker. It runs in its own window and reports back to a BMessenger asynchronously.

## Header and library

- Header: `<FilePanel.h>`
- Library: `libtracker.so` (makefile-engine: `LIBS = be tracker`)

## Key constructors

- `BFilePanel(file_panel_mode mode = B_OPEN_PANEL, BMessenger* target = NULL, const entry_ref* directory = NULL, uint32 nodeFlavors = 0, bool allowMultipleSelection = true, BMessage* message = NULL, BRefFilter* filter = NULL, bool modal = false, bool hideWhenDone = true)`

## Key methods

- Show(), Hide(), IsShowing(), Window().
- SetTarget(BMessenger), SetMessage(BMessage*).
- SetPanelDirectory(const char* / entry_ref* / BEntry* / BDirectory*).
- SetSaveText(const char*), SetButtonLabel(file_panel_button, const char*).
- SetRefFilter(BRefFilter*), Refresh(), Rewind() / GetNextSelectedRef().

## Messages

Open panel: B_REFS_RECEIVED (or your message) with entry_ref `refs` fields. Save panel: B_SAVE_REQUESTED (or your message) with entry_ref `directory` and string `name`. Closing the panel sends B_CANCEL.

## Example

```cpp
BMessenger target(this);
fOpenPanel = new BFilePanel(B_OPEN_PANEL, &target, NULL, B_FILE_NODE,
	true, new BMessage(MSG_OPEN_FILES));
fOpenPanel->Show();

// later: delete fOpenPanel;
```

The gallery's own sample is in `src/pages/FilePanelPage.cpp`.

## Haiku Human Interface Guidelines notes

- Keep one panel per purpose and reuse it, so it remembers its directory.
- Use a BRefFilter to show only files your application can open.
- Link with libtracker (LIBS += tracker in a makefile-engine Makefile).

## Reference

- The Haiku Book: [BFilePanel](https://www.haiku-os.org/docs/api/classBFilePanel.html)
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
