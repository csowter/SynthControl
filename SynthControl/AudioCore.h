#ifndef audiocore_h
#define audiocore_h

#include "Generator.h"
#include <SDL.h>
#include "Biquad.h"
#include "Delay.h"
#include "Envelope.h"

class cAudioCore
{
public:
	struct sSample
	{
		float left;
		float right;
	};

	enum eGenerator
	{
		sine,
		square,
		saw,
	};

	cAudioCore();
	~cAudioCore();
	void MuteOscillators(bool mute, int oscillator);
	void SwitchOscillator(int oscillator);
	void SetGain(int oscillator, float gain);
	void SetDelayGain(float gain){ mDelayTargetGain = gain; }
	void SetPan(float pan){ mPan = pan; }

	eGenerator mGeneratorType[12];
	iGenerator *mGenerators[12];
	cEnvelope mEnvelope;
	uint32_t mEnvelopeSample;

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