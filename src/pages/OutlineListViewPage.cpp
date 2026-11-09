/*
 * Haiku Gallery - BOutlineListView page.
 */
#include "OutlineListViewPage.h"

#include <Button.h>
#include <LayoutBuilder.h>
#include <OutlineListView.h>
#include <ScrollView.h>
#include <String.h>
#include <StringItem.h>

#include <vector>

#include "Messages.h"


OutlineListViewPage::OutlineListViewPage()
	:
	GalleryPage("BOutlineListView"),
	fOutline(NULL),
	fAdded(0)
{
}


OutlineListViewPage::~OutlineListViewPage()
{
	// Like BListView, the outline list does not own its items.
	if (fOutline != NULL) {
		std::vector<BListItem*> items;
		for (int32 i = 0; i < fOutline->FullListCountItems(); i++)
			items.push_back(fOutline->FullListItemAt(i));
		fOutline->MakeEmpty();
		for (size_t i = 0; i < items.size(); i++)
			delete items[i];
	}
}


const char*
OutlineListViewPage::Title() const
{
	return "BOutlineListView";
}


const char*
OutlineListViewPage::Description() const
{
	return "BOutlineListView is a BListView whose items form a tree. Each "
		"item has an outline level; items with children get a disclosure "
		"triangle and can be expanded or collapsed. Functions that start "
		"with FullList work on every item, including the hidden children "
		"of collapsed items; the inherited ones see only visible items.";
}


const char*
OutlineListViewPage::SourceSnippet() const
{
	return
"#include <OutlineListView.h>\n"
"#include <StringItem.h>\n"
"\n"
"BOutlineListView* tree = new BOutlineListView(\"tree\");\n"
"BStringItem* animals = new BStringItem(\"Animals\");\n"
"tree->AddItem(animals);\n"
"tree->AddUnder(new BStringItem(\"Cat\"), animals);\n"
"tree->AddUnder(new BStringItem(\"Dog\"), animals);\n"
"tree->Collapse(animals);\n"
"\n"
"// Visit every item, visible or not:\n"
"for (int32 i = 0; i < tree->FullListCountItems(); i++) {\n"
"\tBListItem* item = tree->FullListItemAt(i);\n"
"\tprintf(\"level %u\\n\", (unsigned)item->OutlineLevel());\n"
"}\n";
}


BView*
OutlineListViewPage::CreateSample()
{
	fOutline = new BOutlineListView("outline");
	fOutline->SetSelectionMessage(new BMessage(MSG_OL_SELECTED));

	BStringItem* animals = new BStringItem("Animals");
	fOutline->AddItem(animals);
	BStringItem* mammals = new BStringItem("Mammals");
	fOutline->AddUnder(mammals, animals);
	fOutline->AddUnder(new BStringItem("Cat"), mammals);
	fOutline->AddUnder(new BStringItem("Dog"), mammals);
	BStringItem* birds = new BStringItem("Birds");
	fOutline->AddUnder(birds, animals);
	fOutline->AddUnder(new BStringItem("Owl"), birds);
	fOutline->AddUnder(new BStringItem("Penguin"), birds);

	BStringItem* plants = new BStringItem("Plants");
	fOutline->AddItem(plants);
	fOutline->AddUnder(new BStringItem("Fern"), plants);
	fOutline->AddUnder(new BStringItem("Oak"), plants);
	fOutline->Collapse(plants);

	BScrollView* scroll = new BScrollView("scroll", fOutline, 0, false,
		true);
	scroll->SetExplicitMinSize(BSize(200, 180));

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(scroll)
		.View();
}


BView*
OutlineListViewPage::CreateOptions()
{
	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(new BButton("expand", "Expand all",
			new BMessage(MSG_OL_EXPAND_ALL)))
		.Add(new BButton("collapse", "Collapse all",
			new BMessage(MSG_OL_COLLAPSE_ALL)))
		.Add(new BButton("addChild", "Add child to selection",
			new BMessage(MSG_OL_ADD_CHILD)))
		.View();
}


bool
OutlineListViewPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_OL_SELECTED:
		{
			int32 index = fOutline->CurrentSelection();
			if (index < 0) {
				LogEvent("Selection cleared");
				return true;
			}
			BStringItem* item = static_cast<BStringItem*>(
				fOutline->ItemAt(index));
			BStringItem* super = static_cast<BStringItem*>(
				fOutline->Superitem(item));
			LogEvent("Selected \"%s\" (level %" B_PRIu32 ", parent: %s)",
				item->Text(), item->OutlineLevel(),
				super != NULL ? super->Text() : "none");
			return true;
		}

		case MSG_OL_EXPAND_ALL:
		case MSG_OL_COLLAPSE_ALL:
		{
			bool expand = message->what == MSG_OL_EXPAND_ALL;
			// Walk backwards so collapsing does not shift what is left.
			for (int32 i = fOutline->FullListCountItems() - 1; i >= 0; i--) {
				BListItem* item = fOutline->FullListItemAt(i);
				if (fOutline->CountItemsUnder(item, true) == 0)
					continue;
				if (expand)
					fOutline->Expand(item);
				else
					fOutline->Collapse(item);
			}
			LogEvent("%s", expand ? "Expanded all items"
				: "Collapsed all items");
			return true;
		}

		case MSG_OL_ADD_CHILD:
		{
			int32 index = fOutline->CurrentSelection();
			if (index < 0) {
				LogEvent("Select an item first");
				return true;
			}
			BListItem* parent = fOutline->ItemAt(index);
			BString label;
			label.SetToFormat("New item %" B_PRId32, ++fAdded);
			fOutline->AddUnder(new BStringItem(label.String()), parent);
			fOutline->Expand(parent);
			LogEvent("AddUnder(\"%s\")", label.String());
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
