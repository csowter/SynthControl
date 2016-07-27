#ifndef sinusoid_h
#define sinusoid_h

#include "Generator.h"

class cSineGenerator : public iGenerator
{
private:
	int mSampleRate;
	float mFrequency;
	float mSum;
	float mIncrement;
	bool mMute;

	void CalculateIncrement();
public:
	cSineGenerator();
	virtual float NextSample();
	virtual void SetSampleRate(uint32_t sampleRate);
	virtual void SetFrequency(float frequency);
	virtual void SetMute(bool mute);
	virtual bool GetMute(){ return mMute; }
};

#endif