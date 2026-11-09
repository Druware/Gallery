# Haiku Gallery architecture

Haiku Gallery is a single-window BApplication written against the public Haiku API (R1/beta5 and later). This document describes how the pieces fit together.

## Overview

```
App (BApplication, src/App.cpp)
 └─ MainWindow (BWindow, src/MainWindow.cpp)
     ├─ BMenuBar                      File / View / Help
     └─ BSplitView
         ├─ navigation pane (BGroupView)
         │   ├─ BTextControl          search filter
         │   └─ BScrollView
         │       └─ NavigationList    BOutlineListView of categories and pages
         └─ BCardView                 one card per page
             ├─ HomePage
             ├─ ButtonPage
             └─ ...                   one GalleryPage subclass per control
```

## Source layout

| Path | Role |
| --- | --- |
| `src/App.cpp/.h` | `App` (BApplication): creates the main window in `ReadyToRun()`, shows the About box in `AboutRequested()`. Contains `main()`. |
| `src/MainWindow.cpp/.h` | Builds the menu bar, navigation pane and card view; switches pages; forwards messages to pages; opens the docs folder and the Haiku Book. |
| `src/NavigationList.cpp/.h` | `NavigationList` (BOutlineListView): rebuilds the category/page tree for a search filter; maps list items to page indexes. |
| `src/PageRegistry.cpp/.h` | The `kPages` table: one line per control page, giving its category and a factory function. |
| `src/Messages.h` | Every `what` code used by the application, as named `const uint32` constants. |
| `src/pages/GalleryPage.cpp/.h` | Abstract base class for a page. Builds the common page layout. |
| `src/pages/HomePage.cpp/.h` | Welcome text and a grid of buttons, one per page, grouped by category. |
| `src/pages/*Page.cpp/.h` | One page per control. |
| `HaikuGallery.rdef` | Application signature, version and flags. |
| `Makefile` | makefile-engine build file. |

## Pages

`GalleryPage` is a `BView` with four pure virtual methods that describe the page and two that create its content:

- `Title()` — shown in the navigation list, the window title and the home page buttons.
- `Description()` — one paragraph shown under the title.
- `SourceSnippet()` — code shown in the read-only source box.
- `BookClass()` — class name for Help ▸ Haiku Book (defaults to `Title()`; the Tooltips page returns `BView`).
- `CreateSample()` — the live sample (required).
- `CreateOptions()` — the options panel (optional; return `NULL` for none).

`Build()` assembles the standard layout: title, description, a "Sample" BBox and an "Options" BBox side by side, the event line, and the source box with a "Copy source" button. Because the layout calls virtual methods, it cannot run in the constructor; `MainWindow` calls `Build()` once, right after creating each page. `HomePage` overrides `Build()` with its own layout.

`LogEvent(format, ...)` writes a printf-style message to the page's event line ("Last event: Value changed: 42").

## Message flow

Controls in pages keep their default target, which is the window. `MainWindow::MessageReceived()` handles its own codes (navigation, search, menu commands) and passes everything else to `_DispatchToPages()`:

1. The visible page's `HandleMessage()` is called first.
2. If it returns `false`, every other page is asked. This matters for asynchronous replies that may arrive after the user has switched pages: file panel results, alert results, and BMessageRunner ticks.
3. If no page claims the message, it goes to `BWindow::MessageReceived()`.

Each page's `HandleMessage()` switches on its own codes from `Messages.h`, returns `true` for those it consumed, and finally calls `GalleryPage::HandleMessage()`, which handles `MSG_COPY_SOURCE` for the copy button. Because codes are unique per page, the order in which pages are asked never changes the outcome.

Views that have no message of their own get a small subclass inside the page's `.cpp` file that posts one to the window: `NotifyingTextView` (BTextView edits), `NotifyingTabView` (BTabView selection) and `PopUpArea` (shows a BPopUpMenu on MouseDown).

## Navigation and search

`NavigationList::Populate(pages, filter)` deletes all items and rebuilds the tree: Home first, then each category in registry order, each followed by its pages. With a non-empty filter, a page is listed when its title contains the filter (case-insensitive), and a whole category is listed when its name matches. Empty categories are left out.

Every item stores a page index (`-1` for category items). Index 0 is the home page; index `i + 1` is `PageAt(i)` from the registry. The same index is the page's position in `MainWindow::fPages` and in the card layout, so showing a page is `fCards->CardLayout()->SetVisibleItem(index)`.

Selecting an item sends `MSG_NAV_SELECTED`; the home page buttons send `MSG_SHOW_PAGE` with an `index` field. `MainWindow::_ShowPage()` ignores the page that is already visible, which prevents loops between list selection and page changes.

## Menus

| Menu | Item | Action |
| --- | --- | --- |
| File | About Haiku Gallery… | Posts `B_ABOUT_REQUESTED` to `be_app` (`App::AboutRequested()`). |
| File | Quit (Alt+Q) | `B_QUIT_REQUESTED`; the window has `B_QUIT_ON_WINDOW_CLOSE`. |
| View | Home (Alt+H) | Shows the home page. |
| View | Show navigation (Alt+N) | Collapses or restores the navigation pane with `BSplitView::SetItemCollapsed()`. |
| View | Find control… (Alt+F) | Focuses the search field. |
| Help | Open documentation folder | Sends `B_REFS_RECEIVED` to Tracker for the `docs` folder next to the executable or, failing that, in its parent folder (the source tree when run from `objects.*/`). |
| Help | Haiku Book page for this control (Alt+B) | Launches the URL handler for `https://www.haiku-os.org/docs/api/class<Name>.html`. |
| Help | About Haiku Gallery… | Same as File ▸ About. |

## Ownership

- Pages are children of the card view and are deleted with the window.
- List views do not own their items, so `NavigationList`, `ListViewPage` and `OutlineListViewPage` delete their items in their destructors.
- `FilePanelPage` owns its `BFilePanel`; `StatusBarPage` owns its `BMessageRunner`.
- BAlerts delete themselves; `BAlert::Go(BInvoker*)` takes ownership of the invoker.

## Adding a control page

1. Add the message codes you need to `src/Messages.h`, with a new unique prefix.
2. Create `src/pages/FooPage.h` and `src/pages/FooPage.cpp` subclassing `GalleryPage`; implement `Title()`, `Description()`, `SourceSnippet()`, `CreateSample()`, optionally `CreateOptions()`, and `HandleMessage()`, ending with `return GalleryPage::HandleMessage(message);`.
3. Add `#include "FooPage.h"` and one line `{ "Category", &Create<FooPage> },` to `kPages` in `src/PageRegistry.cpp`.
4. Add `src/pages/FooPage.cpp` to `SRCS` in the `Makefile`.
5. Add `docs/controls/BFoo.md` and a line in `docs/index.md`.

The navigation list, the search, the home page and the Haiku Book link pick up the new page automatically.
