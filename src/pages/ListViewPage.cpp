/*
 * Haiku Gallery - BListView page.
 */
#include "ListViewPage.h"

#include <Button.h>
#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <ListView.h>
#include <ScrollView.h>
#include <String.h>
#include <StringItem.h>
#include <TextControl.h>

#include "Messages.h"


static const char* kFruits[] = {
	"Apple", "Banana", "Cherry", "Grape", "Lemon", "Mango", "Orange",
	"Peach", "Pear", "Plum"
};


ListViewPage::ListViewPage()
	:
	GalleryPage("BListView"),
	fList(NULL),
	fMultiple(NULL),
	fNewItem(NULL)
{
}


ListViewPage::~ListViewPage()
{
	// A BListView does not own its items.
	if (fList != NULL) {
		for (int32 i = fList->CountItems() - 1; i >= 0; i--)
			delete fList->RemoveItem(i);
	}
}


const char*
ListViewPage::Title() const
{
	return "BListView";
}


const char*
ListViewPage::Description() const
{
	return "BListView shows a scrolling list of BListItem objects, usually "
		"BStringItem. It sends its selection message when the selection "
		"changes and its invocation message on a double-click or Enter. "
		"The list does not own its items: delete them yourself when you "
		"remove them or destroy the list.";
}


const char*
ListViewPage::SourceSnippet() const
{
	return
"#include <ListView.h>\n"
"#include <ScrollView.h>\n"
"#include <StringItem.h>\n"
"\n"
"BListView* list = new BListView(\"fruits\", B_SINGLE_SELECTION_LIST);\n"
"list->AddItem(new BStringItem(\"Apple\"));\n"
"list->AddItem(new BStringItem(\"Banana\"));\n"
"list->SetSelectionMessage(new BMessage(MSG_SELECTED));\n"
"list->SetInvocationMessage(new BMessage(MSG_INVOKED));\n"
"\n"
"BScrollView* scroll = new BScrollView(\"scroll\", list, 0,\n"
"\tfalse, true);\n"
"\n"
"// In MessageReceived():\n"
"case MSG_SELECTED:\n"
"{\n"
"\tint32 index = list->CurrentSelection();\n"
"\tif (index >= 0) {\n"
"\t\tBStringItem* item = (BStringItem*)list->ItemAt(index);\n"
"\t\tprintf(\"%s\\n\", item->Text());\n"
"\t}\n"
"\tbreak;\n"
"}\n";
}


BView*
ListViewPage::CreateSample()
{
	fList = new BListView("list", B_SINGLE_SELECTION_LIST);
	for (size_t i = 0; i < sizeof(kFruits) / sizeof(kFruits[0]); i++)
		fList->AddItem(new BStringItem(kFruits[i]));
	fList->SetSelectionMessage(new BMessage(MSG_LV_SELECTED));
	fList->SetInvocationMessage(new BMessage(MSG_LV_INVOKED));

	BScrollView* scroll = new BScrollView("scroll", fList, 0, false, true);
	scroll->SetExplicitMinSize(BSize(200, 160));

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(scroll)
		.View();
}


BView*
ListViewPage::CreateOptions()
{
	fMultiple = new BCheckBox("multiple", "Multiple selection",
		new BMessage(MSG_LV_MULTIPLE));
	fNewItem = new BTextControl("newItem", "New item:", "Kiwi",
		new BMessage(MSG_LV_ADD));

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fMultiple)
		.Add(fNewItem)
		.AddGroup(B_HORIZONTAL)
			.Add(new BButton("add", "Add", new BMessage(MSG_LV_ADD)))
			.Add(new BButton("remove", "Remove selected",
				new BMessage(MSG_LV_REMOVE)))
		.End()
		.View();
}


bool
ListViewPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_LV_SELECTED:
		{
			BString selected;
			int32 count = 0;
			for (int32 i = 0; fList->CurrentSelection(i) >= 0; i++) {
				BStringItem* item = static_cast<BStringItem*>(
					fList->ItemAt(fList->CurrentSelection(i)));
				if (count++ > 0)
					selected << ", ";
				selected << item->Text();
			}
			if (count == 0)
				LogEvent("Selection cleared");
			else
				LogEvent("Selected: %s", selected.String());
			return true;
		}

		case MSG_LV_INVOKED:
		{
			int32 index = fList->CurrentSelection();
			if (index >= 0) {
				LogEvent("Invoked: %s", static_cast<BStringItem*>(
					fList->ItemAt(index))->Text());
			}
			return true;
		}

		case MSG_LV_MULTIPLE:
		{
			bool multiple = fMultiple->Value() == B_CONTROL_ON;
			fList->SetListType(multiple
				? B_MULTIPLE_SELECTION_LIST : B_SINGLE_SELECTION_LIST);
			LogEvent("SetListType(%s)", multiple
				? "B_MULTIPLE_SELECTION_LIST" : "B_SINGLE_SELECTION_LIST");
			return true;
		}

		case MSG_LV_ADD:
		{
			BString text(fNewItem->Text());
			text.Trim();
			if (text.IsEmpty())
				return true;
			fList->AddItem(new BStringItem(text.String()));
			fList->Select(fList->CountItems() - 1);
			fList->ScrollToSelection();
			LogEvent("AddItem(\"%s\")", text.String());
			return true;
		}

		case MSG_LV_REMOVE:
		{
			int32 removed = 0;
			int32 index;
			while ((index = fList->CurrentSelection()) >= 0) {
				delete fList->RemoveItem(index);
				removed++;
			}
			LogEvent("Removed %" B_PRId32 " item(s)", removed);
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
