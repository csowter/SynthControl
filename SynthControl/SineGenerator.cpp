#include "SineGenerator.h"
#define _USE_MATH_DEFINES
#include <cmath>

cSineGenerator::cSineGenerator()
	: mSum(0.0f), mIncrement(0.0f)
{

}

void cSineGenerator::SetFrequency(float frequency)
{
	mFrequency = frequency;
	CalculateIncrement();
}

void cSineGenerator::SetSampleRate(uint32_t sampleRate)
{
	mSampleRate = sampleRate;
	CalculateIncrement();
}

void cSineGenerator::SetMute(bool mute)
{
	mMute = mute;
}

float cSineGenerator::NextSample()
{
	if (mMute)
		return 0.0f;
	mSum = mSum + mIncrement;
	float sample = sin(mSum);
	
	return sample;
}

void cSineGenerator::CalculateIncrement()
{
	mIncrement = (2 * M_PI * mFrequency) / mSampleRate;
}