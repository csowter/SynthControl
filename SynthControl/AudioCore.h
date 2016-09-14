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
	void SetDelayGain(float gain){ mDelayTargetGain = gain; }
	void SetPan(float pan){ mPan = pan; }

	bool mGeneratorType[12];
	iGenerator *mGenerators[12];

	bool mMute[12];

	float mGain[12];
	float mTargetGain[12];
	float mPan;
	cBiquad mBiquad;
	cBiquad mBiquad1;
	cDelay mDelay[2];
	float mDelayGain;
	float mDelayTargetGain;

	sSample NextSample();

	float GetMeterValue(int meter) const;

private:
	SDL_AudioDeviceID mAudioDevice;
	static const int MeterBufferLength = 512;
	float mMeterBuffer[2][MeterBufferLength];
	uint32_t mMeterIndex;
	void OpenAudioDevice();
};

#endif