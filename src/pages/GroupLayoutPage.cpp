/*
 * Haiku Gallery - BGroupLayout page.
 */
#include "GroupLayoutPage.h"

#include <Button.h>
#include <CheckBox.h>
#include <GroupLayout.h>
#include <GroupView.h>
#include <LayoutBuilder.h>
#include <Slider.h>

#include "Messages.h"


GroupLayoutPage::GroupLayoutPage()
	:
	GalleryPage("BGroupLayout"),
	fGroup(NULL),
	fVertical(NULL),
	fSpacing(NULL),
	fInsets(NULL),
	fWeights(NULL)
{
}


const char*
GroupLayoutPage::Title() const
{
	return "BGroupLayout";
}


const char*
GroupLayoutPage::Description() const
{
	return "BGroupLayout arranges items in a single row or column. Spacing "
		"goes between items, insets around them, and each item's weight "
		"decides how extra space is shared. BLayoutBuilder::Group is the "
		"usual way to build one; nest groups to build most dialogs. The "
		"buttons below stretch because their maximum width is unlimited.";
}


const char*
GroupLayoutPage::SourceSnippet() const
{
	return
"#include <LayoutBuilder.h>\n"
"\n"
"BLayoutBuilder::Group<>(this, B_HORIZONTAL, B_USE_DEFAULT_SPACING)\n"
"\t.SetInsets(B_USE_WINDOW_INSETS)\n"
"\t.Add(one, 1.0f)      // weight 1\n"
"\t.Add(two, 2.0f)      // gets twice the extra space\n"
"\t.AddGlue()           // flexible empty space\n"
"\t.Add(three);\n"
"\n"
"// Change it later through the layout object:\n"
"BGroupLayout* layout = (BGroupLayout*)GetLayout();\n"
"layout->SetOrientation(B_VERTICAL);\n"
"layout->SetSpacing(20);\n"
"layout->SetItemWeight(1, 2.0f);\n";
}


BView*
GroupLayoutPage::CreateSample()
{
	BGroupView* groupView = new BGroupView(B_HORIZONTAL);
	groupView->SetViewUIColor(B_DOCUMENT_BACKGROUND_COLOR);
	fGroup = groupView->GroupLayout();
	fGroup->SetInsets(10);

	const char* labels[] = { "One", "Two", "Three" };
	for (int32 i = 0; i < 3; i++) {
		BButton* button = new BButton(labels[i], labels[i], NULL);
		button->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED, B_SIZE_UNLIMITED));
		fGroup->AddView(button);
	}

	groupView->SetExplicitMinSize(BSize(260, 140));
	return groupView;
}


static BSlider*
MakeSlider(const char* name, const char* label, uint32 what, int32 value)
{
	BSlider* slider = new BSlider(name, label, new BMessage(what), 0, 40,
		B_HORIZONTAL);
	slider->SetModificationMessage(new BMessage(what));
	slider->SetHashMarks(B_HASH_MARKS_BOTTOM);
	slider->SetHashMarkCount(5);
	slider->SetLimitLabels("0", "40");
	slider->SetValue(value);
	return slider;
}


BView*
GroupLayoutPage::CreateOptions()
{
	fVertical = new BCheckBox("vertical", "Vertical",
		new BMessage(MSG_GL_VERTICAL));
	fSpacing = MakeSlider("spacing", "Spacing", MSG_GL_SPACING, 5);
	fInsets = MakeSlider("insets", "Insets", MSG_GL_INSETS, 10);
	fWeights = new BCheckBox("weights", "Weights 1 : 2 : 1",
		new BMessage(MSG_GL_WEIGHTS));

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fVertical)
		.Add(fSpacing)
		.Add(fInsets)
		.Add(fWeights)
		.View();
}


bool
GroupLayoutPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_GL_VERTICAL:
		{
			bool vertical = fVertical->Value() == B_CONTROL_ON;
			fGroup->SetOrientation(vertical ? B_VERTICAL : B_HORIZONTAL);
			LogEvent("SetOrientation(%s)",
				vertical ? "B_VERTICAL" : "B_HORIZONTAL");
			return true;
		}

		case MSG_GL_SPACING:
			fGroup->SetSpacing(fSpacing->Value());
			LogEvent("SetSpacing(%" B_PRId32 ")", fSpacing->Value());
			return true;

		case MSG_GL_INSETS:
			fGroup->SetInsets(fInsets->Value());
			LogEvent("SetInsets(%" B_PRId32 ")", fInsets->Value());
			return true;

		case MSG_GL_WEIGHTS:
		{
			bool weighted = fWeights->Value() == B_CONTROL_ON;
			fGroup->SetItemWeight(1, weighted ? 2.0f : 1.0f);
			LogEvent("SetItemWeight(1, %s)", weighted ? "2.0" : "1.0");
			return true;
		}
	}
	return GalleryPage::HandleMessage(message);
}
