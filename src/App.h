/*
 * Haiku Gallery - application object.
 */
#ifndef APP_H
#define APP_H

#include <Application.h>


extern const char* kAppSignature;


class App : public BApplication {
public:
								App();

	virtual	void				ReadyToRun();
	virtual	void				AboutRequested();
};

#endif	// APP_H
