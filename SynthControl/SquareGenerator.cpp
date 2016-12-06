#include "SquareGenerator.h"
#include <cmath>

cSquareGenerator::cSquareGenerator()
	: mCount(0), mState(0.0f)
{
}

void cSquareGenerator::SetFrequency(float frequency)
{
	mFrequency = frequency;
	mToggle = static_cast<uint32_t>((mSampleRate / frequency) / 2);
}

void cSquareGenerator::SetSampleRate(uint32_t sampleRate)
{
	mSampleRate = sampleRate;
}

float cSquareGenerator::NextSample()
{
	mCount++;
	if (mCount >= mToggle)
	{
		mCount = 0;
		if (mState == 1.0f)
			mState = 0.0f;
		else
			mState = 1.0f;
	}

	return mState;
}
