#ifndef audiocore_h
#define audiocore_h

#include "Generator.h"
#include <SDL.h>
#include "Biquad.h"
#include "Delay.h"

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

	bool mMute[12];

	float mGain[12];
	float mTargetGain[12];
	cBiquad mBiquad;
	cBiquad mBiquad1;
	cDelay mDelay;

	float NextSample();

	float GetLeftMeterValue() const { return mLeftMeterValue; }
	float GetRightMeterValue() const { return mRightMeterValue;	}

	float mLeftMeterValue;
	float mRightMeterValue;
private:
	
	void OpenAudioDevice();
};

#endif