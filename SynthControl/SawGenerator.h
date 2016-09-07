#ifndef sawgenerator_h
#define sawgenerator_h

#include "Generator.h"

class cSawGenerator : public iGenerator
{
private:
	int mSampleRate;
	float mFrequency;
	float mSum;
	float mIncrement;

	void CalculateIncrement();
public:
	cSawGenerator();
	virtual float NextSample();
	virtual void SetSampleRate(uint32_t sampleRate);
	virtual void SetFrequency(float frequency);
};


#endif