#include "SawGenerator.h"
#include <cmath>

cSawGenerator::cSawGenerator()
	: mSum(0.0f), mIncrement(0.0f)
{

}

void cSawGenerator::SetFrequency(float frequency)
{
	mFrequency = frequency;
	CalculateIncrement();
}

void cSawGenerator::SetSampleRate(uint32_t sampleRate)
{
	mSampleRate = sampleRate;
	CalculateIncrement();
}

void cSawGenerator::SetMute(bool mute)
{
	mMute = mute;
}

float cSawGenerator::NextSample()
{
	if (mMute)
		return 0.0f;

	if(mSum >= 0.9f)
		mSum = -0.9f;
	mSum += mIncrement;
	if(mSum > 0.9f)
		mSum = 0.9f;
	return mSum;
}

void cSawGenerator::CalculateIncrement()
{
	mIncrement = 2.0f / (mSampleRate / mFrequency);
}