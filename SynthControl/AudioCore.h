#ifndef audiocore_h
#define audiocore_h

#include "Sinusoid.h"
#include <SDL.h>

class cAudioCore
{
public:
	cAudioCore();
	~cAudioCore();

private:
	Sinusoid mSine;
	void OpenAudioDevice();
};

#endif