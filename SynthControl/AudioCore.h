#ifndef audiocore_h
#define audiocore_h

#include "Sinusoid.h"
#include <SDL.h>

class cAudioCore
{
public:
	cAudioCore();
	~cAudioCore();
	void cAudioCore::MuteOscillators(bool mute, int oscillator);
private:
	Sinusoid mSine[12];
	void OpenAudioDevice();
};

#endif