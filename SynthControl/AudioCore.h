#ifndef audiocore_h
#define audiocore_h

#include "Generator.h"
#include <SDL.h>

class cAudioCore
{
public:
	cAudioCore();
	~cAudioCore();
	void MuteOscillators(bool mute, int oscillator);
	void SwitchOscillator(int oscillator);
private:
	bool mGeneratorType[12];
	iGenerator *mGenerators[12];
	void OpenAudioDevice();
};

#endif