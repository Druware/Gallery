/*
 * Haiku Gallery - BTextView page.
 */
#include "TextViewPage.h"

#include <CheckBox.h>
#include <LayoutBuilder.h>
#include <ScrollView.h>
#include <TextView.h>
#include <Window.h>

#include "Messages.h"


namespace {

// BTextView has no change notification, so this subclass posts
// MSG_TV_CHANGED to its window whenever text is inserted or deleted.
class NotifyingTextView : public BTextView {
public:
	NotifyingTextView(const char* name)
		:
		BTextView(name)
	{
	}

protected:
	virtual void InsertText(const char* text, int32 length, int32 offset,
		const text_run_array* runs)
	{
		BTextView::InsertText(text, length, offset, runs);
		_Notify();
	}

	virtual void DeleteText(int32 fromOffset, int32 toOffset)
	{
		BTextView::DeleteText(fromOffset, toOffset);
		_Notify();
	}

private:
	void _Notify()
	{
		if (Window() != NULL)
			Window()->PostMessage(MSG_TV_CHANGED);
	}
};

}	// namespace


TextViewPage::TextViewPage()
	:
	GalleryPage("BTextView"),
	fTextView(NULL),
	fEditable(NULL),
	fSelectable(NULL),
	fWordWrap(NULL)
{
}


const char*
TextViewPage::Title() const
{
	return "BTextView";
}


const char*
TextViewPage::Description() const
{
	return "BTextView is a multi-line text editor with optional styled "
		"text, undo, and clipboard support. Wrap it in a BScrollView to "
		"get scroll bars. It sends no messages of its own; subclass it and "
		"override InsertText() and DeleteText() to be told about edits, as "
		"this sample does.";
}


const char*
TextViewPage::SourceSnippet() const
{
	return
"#include <ScrollView.h>\n"
"#include <TextView.h>\n"
"\n"
"BTextView* text = new BTextView(\"notes\");\n"
"text->SetText(\"Type here\");\n"
"text->SetWordWrap(true);\n"
"text->SetStylable(true);\n"
"text->MakeEditable(true);\n"
"\n"
"BScrollView* scroll = new BScrollView(\"scroll\", text, 0,\n"
"\tfalse, true);   // no horizontal, vertical scroll bar\n"
"\n"
"// Be told about edits:\n"
"class MyTextView : public BTextView {\n"
"protected:\n"
"\tvirtual void InsertText(const char* text, int32 length,\n"
"\t\tint32 offset, const text_run_array* runs)\n"
"\t{\n"
"\t\tBTextView::InsertText(text, length, offset, runs);\n"
"\t\tWindow()->PostMessage(MSG_TEXT_CHANGED);\n"
"\t}\n"
"};\n";
}


BView*
TextViewPage::CreateSample()
{
	fTextView = new NotifyingTextView("text");
	fTextView->SetText("Haiku is an open-source operating system that "
		"specifically targets personal computing. Inspired by BeOS, Haiku "
		"is fast, simple to use, easy to learn and yet very powerful.\n\n"
		"Edit this text, select some of it, and try the options.");
	fTextView->SetWordWrap(true);
	fTextView->SetStylable(true);

	BScrollView* scroll = new BScrollView("scroll", fTextView, 0, true, true);
	scroll->SetExplicitMinSize(BSize(260, 120));

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(scroll)
		.View();
}


BView*
TextViewPage::CreateOptions()
{
	fEditable = new BCheckBox("editable", "Editable",
		new BMessage(MSG_TV_EDITABLE));
	fEditable->SetValue(B_CONTROL_ON);
	fSelectable = new BCheckBox("selectable", "Selectable",
		new BMessage(MSG_TV_SELECTABLE));
	fSelectable->SetValue(B_CONTROL_ON);
	fWordWrap = new BCheckBox("wordWrap", "Word wrap",
		new BMessage(MSG_TV_WORDWRAP));
	fWordWrap->SetValue(B_CONTROL_ON);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fEditable)
		.Add(fSelectable)
		.Add(fWordWrap)
		.View();
}


bool
TextViewPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_TV_CHANGED:
			LogEvent("Text changed: %" B_PRId32 " bytes, %" B_PRId32
				" lines", fTextView->TextLength(), fTextView->CountLines());
			return true;

		case MSG_TV_EDITABLE:
		{
			bool editable = fEditable->Value() == B_CONTROL_ON;
			fTextView->MakeEditable(editable);
			LogEvent("MakeEditable(%s)", editable ? "true" : "false");
			return true;
		}

		case MSG_TV_SELECTABLE:
		{
			bool selectable = fSelectable->Value() == B_CONTROL_ON;
			fTextView->MakeSelectable(selectable);
			LogEvent("MakeSelectable(%s)", selectable ? "true" : "false");
			return true;
		}

		case MSG_TV_WORDWRAP:
		{
			bool wrap = fWordWrap->Value() == B_CONTROL_ON;
			fTextView->SetWordWrap(wrap);
			LogEvent("SetWordWrap(%s)", wrap ? "true" : "false");
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
