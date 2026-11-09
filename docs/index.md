# Haiku Gallery documentation

One page per control showcased in Haiku Gallery, grouped as in the application's navigation list. See [architecture.md](architecture.md) for how the application itself is built.

## Basic input

- [BButton](controls/BButton.md) — A push button.
- [BCheckBox](controls/BCheckBox.md) — An on/off control with a label, used for independent options.
- [BRadioButton](controls/BRadioButton.md) — A control for choosing exactly one option from a small set.
- [BSlider](controls/BSlider.md) — A control for picking an integer in a range by dragging a thumb along a bar.

## Text

- [BStringView](controls/BStringView.md) — Draws one line of static text.
- [BTextControl](controls/BTextControl.md) — A labelled single-line text field.
- [BTextView](controls/BTextView.md) — A multi-line text editing view with optional styled text, word wrapping, undo and clipboard support.

## Collections

- [BListView](controls/BListView.md) — A scrolling list of BListItem objects (usually BStringItem), with single or multiple selection.
- [BOutlineListView](controls/BOutlineListView.md) — A BListView whose items form a tree.

## Menus & selection

- [BMenuBar](controls/BMenuBar.md) — The bar of menus at the top of a window.
- [BPopUpMenu](controls/BPopUpMenu.md) — A menu that appears on demand, typically as a context menu at the mouse position.
- [BMenuField](controls/BMenuField.md) — A label plus a pop-up menu that shows the currently selected item; Haiku's drop-down list.
- [BOptionPopUp](controls/BOptionPopUp.md) — A BControl (via BOptionControl) wrapping a BMenuField.

## Status & info

- [BStatusBar](controls/BStatusBar.md) — A progress bar with labels: a leading label and trailing label above the bar, each followed by optional text.
- [BAlert](controls/BAlert.md) — A small modal window with an icon, a message and up to three buttons.
- [Tooltips](controls/Tooltips.md) — Every BView can show a tooltip after the mouse rests over it.

## Layout

- [BGroupLayout](controls/BGroupLayout.md) — Arranges items in one row or one column, with spacing between items, insets around them and per-item weights.
- [BGridLayout](controls/BGridLayout.md) — Places items in rows and columns; items can span several cells.
- [BSplitView](controls/BSplitView.md) — Lays out children in a row or column with draggable splitters between them.
- [BCardLayout](controls/BCardLayout.md) — Stacks items like cards and shows only one at a time.
- [BTabView](controls/BTabView.md) — Shows one of several views, chosen with tabs.
- [BBox](controls/BBox.md) — Draws a frame around related controls, with an optional label in the top border.
- [BScrollView](controls/BScrollView.md) — Wraps a target view with horizontal and/or vertical BScrollBar objects and a border.
- [BSeparatorView](controls/BSeparatorView.md) — A horizontal or vertical line that divides parts of a layout, optionally with a label set into the line.

## Pickers

- [BColorControl](controls/BColorControl.md) — Haiku's built-in color picker: red, green and blue ramps with text fields for exact values (a palette of 256 cells on 8-bit screens).
- [BFilePanel](controls/BFilePanel.md) — The standard Open and Save dialog, provided by Tracker.

## External references

- The Haiku Book (API reference): https://www.haiku-os.org/docs/api/
- Haiku Human Interface Guidelines: https://www.haiku-os.org/docs/HIG/
