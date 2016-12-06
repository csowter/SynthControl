#ifndef squaregenerator_h
#define squaregenerator_h

#include "Generator.h"

class cSquareGenerator : public iGenerator
{
private:
	int mSampleRate;
	float mFrequency;
	uint32_t mCount;
	uint32_t mToggle;
	float mState;

public:
	cSquareGenerator();
	virtual float NextSample();
	virtual void SetSampleRate(uint32_t sampleRate);
	virtual void SetFrequency(float frequency);
};


#endif