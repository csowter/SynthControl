#ifndef audiocore_h
#define audiocore_h

#include "Generator.h"
#include <SDL.h>
#include "Biquad.h"
#include "Delay.h"

class cAudioCore
{
public:
	struct sSample
	{
		float left;
		float right;
	};

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
	float mPan;
	cBiquad mBiquad;
	cBiquad mBiquad1;
	cDelay mDelay;

	sSample NextSample();

	float GetMeterValue(int meter) const;

private:
	static const int MeterBufferLength = 2048;
	float mMeterBuffer[2][MeterBufferLength];
	uint32_t mMeterIndex;
	void OpenAudioDevice();
};

#endif