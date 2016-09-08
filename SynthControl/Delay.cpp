#include "Delay.h"

cDelay::cDelay()
	: mDelayBuffer(new float[1000]()), mDelayLength(1000), mOutPosition(1), mInPosition(0)
{
	ZeroBuffer();
}

cDelay::cDelay(uint32_t delayLength)
	: mDelayBuffer(new float[delayLength]()), mDelayLength(delayLength), mOutPosition(1), mInPosition(0)
{
	ZeroBuffer();
}

cDelay::~cDelay()
{
	delete[] mDelayBuffer;
}

void cDelay::ZeroBuffer()
{
	for (uint32_t i = 0; i < mDelayLength; i++)
		mDelayBuffer[i] = 0.0f;
}

void cDelay::SetDelayLength(uint32_t size)
{
	delete[] mDelayBuffer;
	mDelayLength = size;
	mDelayBuffer = new float[mDelayLength];
	mOutPosition = 1;
	mInPosition = 0;
	ZeroBuffer();
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