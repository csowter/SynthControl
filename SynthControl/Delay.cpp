#include "Delay.h"

cDelay::cDelay(uint32_t delayLength)
	: mDelayBuffer(new float[delayLength]()), mDelayLength(delayLength), mOutPosition(1), mInPosition(0)
{
	for (uint32_t i = 0; i < mDelayLength; i++)
		mDelayBuffer[i] = 0.0f; 
}

cDelay::~cDelay()
{
	delete[] mDelayBuffer;
}

void cDelay::WriteSample(float sampleIn)
{
	mDelayBuffer[mInPosition] = sampleIn;
	mInPosition++;

	if (mInPosition == mDelayLength) 
		mInPosition = 0;
}

float cDelay::ReadSample()
{
	float sampleOut = mDelayBuffer[mOutPosition];
	mOutPosition++;
	if (mOutPosition == mDelayLength)
		mOutPosition = 0;

	return sampleOut;
}