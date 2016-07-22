#include "Sinusoid.h"
#include <cmath>

Sinusoid::Sinusoid(float frequency, int sampleRate)
	: mSampleRate(sampleRate), mSum(0.0f), mMute(false)
{
	SetFrequency(frequency);
}

void Sinusoid::SetFrequency(float frequency)
{
	mTargetFrequency = frequency;
	if (mFrequency != mTargetFrequency)
	{
		mFrequency = mTargetFrequency;
		mIncrement = (2 * M_PI * mFrequency) / mSampleRate;
	}
}

float Sinusoid::NextSample()
{
	if (mMute)
		return 0.0f;
	mSum = mSum + mIncrement;
	float sample = sin(mSum);
	
	mPreviousSample = sample;
	return sample;
}