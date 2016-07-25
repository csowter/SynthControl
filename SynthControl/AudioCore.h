#ifndef audiocore_h
#define audiocore_h

#include "Oscillator.h"
#include <SDL.h>

class cAudioCore
{
public:
	cAudioCore();
	~cAudioCore();
	void cAudioCore::MuteOscillators(bool mute, int oscillator);
private:
	cOscillator mOscillators[12];
	void OpenAudioDevice();
};

#endif