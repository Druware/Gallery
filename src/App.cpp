/*
 * Haiku Gallery - application object.
 */
#include "App.h"

#include <Alert.h>

#include "MainWindow.h"


const char* kAppSignature = "application/x-vnd.Druware-HaikuGallery";


App::App()
	:
	BApplication(kAppSignature)
{
}


void
App::ReadyToRun()
{
	MainWindow* window = new MainWindow();
	window->Show();
}


void
App::AboutRequested()
{
	BAlert* alert = new BAlert("About Haiku Gallery",
		"Haiku Gallery 1.0\n\n"
		"An interactive tour of the Haiku Interface Kit: every page shows "
		"a live control, options that change it at run time, the messages "
		"it sends, and a source snippet you can copy.\n\n"
		"Modeled on the WinUI 3 Gallery.\n"
		"© 2026 Druware",
		"OK");
	alert->SetShortcut(0, B_ESCAPE);
	alert->Go(NULL);
}


int
main()
{
	App app;
	app.Run();
	return 0;
}
