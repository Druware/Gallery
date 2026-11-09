/*
 * Haiku Gallery - BCardLayout / BCardView page.
 */
#include "CardLayoutPage.h"

#include <Button.h>
#include <CardLayout.h>
#include <CardView.h>
#include <LayoutBuilder.h>
#include <OptionPopUp.h>
#include <String.h>
#include <StringView.h>

#include "Messages.h"


static const int32 kCardCount = 3;
static const char* kCardTexts[] = {
	"Step 1: choose a destination folder.",
	"Step 2: pick the files to copy.",
	"Step 3: review and press Copy."
};


CardLayoutPage::CardLayoutPage()
	:
	GalleryPage("BCardLayout"),
	fCards(NULL),
	fPick(NULL)
{
}


const char*
CardLayoutPage::Title() const
{
	return "BCardLayout";
}


const char*
CardLayoutPage::Description() const
{
	return "BCardLayout stacks its items like a deck of cards and shows "
		"only one at a time; the others are hidden. It suits wizards and "
		"preference panels driven by a list. BCardView is a view with a "
		"BCardLayout already set. This gallery's content area is a "
		"BCardView with one card per page.";
}


const char*
CardLayoutPage::SourceSnippet() const
{
	return
"#include <CardLayout.h>\n"
"#include <CardView.h>\n"
"\n"
"BCardView* cards = new BCardView(\"wizard\");\n"
"cards->CardLayout()->AddView(stepOne);\n"
"cards->CardLayout()->AddView(stepTwo);\n"
"cards->CardLayout()->AddView(stepThree);\n"
"\n"
"// Show the second card:\n"
"cards->CardLayout()->SetVisibleItem(1);\n"
"int32 current = cards->CardLayout()->VisibleIndex();\n";
}


BView*
CardLayoutPage::CreateSample()
{
	BCardView* cardView = new BCardView("cards");
	fCards = cardView->CardLayout();
	for (int32 i = 0; i < kCardCount; i++) {
		BString title;
		title.SetToFormat("Card %" B_PRId32, i + 1);
		BView* card = BLayoutBuilder::Group<>(B_VERTICAL)
			.SetInsets(B_USE_DEFAULT_SPACING)
			.Add(new BStringView("title", title.String()))
			.Add(new BStringView("text", kCardTexts[i]))
			.AddGlue()
			.View();
		fCards->AddView(card);
	}
	fCards->SetVisibleItem((int32)0);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(cardView)
		.AddGroup(B_HORIZONTAL)
			.Add(new BButton("previous", "\xE2\x97\x80 Previous",
				new BMessage(MSG_CL_PREVIOUS)))
			.Add(new BButton("next", "Next \xE2\x96\xB6",
				new BMessage(MSG_CL_NEXT)))
			.AddGlue()
		.End()
		.View();
}


BView*
CardLayoutPage::CreateOptions()
{
	fPick = new BOptionPopUp("pick", "Visible card:",
		new BMessage(MSG_CL_PICK));
	for (int32 i = 0; i < kCardCount; i++) {
		BString name;
		name.SetToFormat("Card %" B_PRId32, i + 1);
		fPick->AddOption(name.String(), i);
	}
	fPick->SetValue(0);

	return BLayoutBuilder::Group<>(B_VERTICAL)
		.Add(fPick)
		.View();
}


void
CardLayoutPage::_Show(int32 index)
{
	index = (index + kCardCount) % kCardCount;
	fCards->SetVisibleItem(index);
	fPick->SetValue(index);
	LogEvent("SetVisibleItem(%" B_PRId32 "): card %" B_PRId32 " of %"
		B_PRId32, index, index + 1, kCardCount);
}


bool
CardLayoutPage::HandleMessage(BMessage* message)
{
	switch (message->what) {
		case MSG_CL_PREVIOUS:
			_Show(fCards->VisibleIndex() - 1);
			return true;

		case MSG_CL_NEXT:
			_Show(fCards->VisibleIndex() + 1);
			return true;

		case MSG_CL_PICK:
			_Show(fPick->Value());
			return true;
	}
	return GalleryPage::HandleMessage(message);
}
