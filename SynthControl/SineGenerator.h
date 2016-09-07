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

	void CalculateIncrement();
public:
	cSineGenerator();
	virtual float NextSample();
	virtual void SetSampleRate(uint32_t sampleRate);
	virtual void SetFrequency(float frequency);
};

#endif