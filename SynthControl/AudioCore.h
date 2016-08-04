#ifndef audiocore_h
#define audiocore_h

#include "Generator.h"
#include <SDL.h>
#include "Biquad.h"

class cAudioCore
{
public:
	cAudioCore();
	~cAudioCore();
	void MuteOscillators(bool mute, int oscillator);
	void SwitchOscillator(int oscillator);

	bool mGeneratorType[12];
	iGenerator *mGenerators[12];
	cBiquad mBiquad;
	cBiquad mBiquad1;
private:
	
	void OpenAudioDevice();
};

#endif