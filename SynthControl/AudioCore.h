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
	void SetGain(int oscillator, float gain);

	bool mGeneratorType[12];
	iGenerator *mGenerators[12];
	float mGain[12];
	cBiquad mBiquad;
	cBiquad mBiquad1;
private:
	
	void OpenAudioDevice();
};

#endif