#include "Oscillator.h"
#define _USE_MATH_DEFINES
#include <cmath>

cOscillator::cOscillator()
	: mMute(true)
{

}

cOscillator::cOscillator(float frequency, int sampleRate, cOscillator::eType type)
	:mFrequency(frequency), mSampleRate(sampleRate), mType(type), mMute(true)
{
	switch(mType)
	{
		case Sine:
			mIncrement = (2 * M_PI * mFrequency) / mSampleRate;
			break;
		case Saw:
			mIncrement = 2.0f / (mSampleRate / mFrequency);
			break;
		case Square:
			break;
		case Triangle:
			mIncrement = (2.0f / (mSampleRate / mFrequency)) / 2.0f;
			break;
	}
}

float cOscillator::NextSample()
{
	if(mMute)
		return 0.0f;
	switch(mType)
	{
	case Sine:
		return SineSample();
		break;
	case Saw:
		return SawSample();
		break;
	case Square:
		return SquareSample();
		break;
	case Triangle:
		return TriangleSample();
		break;
	case White:
		return WhiteSample();
		break;
	}
}

void cOscillator::SetType(cOscillator::eType type)
{
	mType = type;
}

float cOscillator::SineSample()
{
	
	mSum = mSum + mIncrement;
	float sample = sin(mSum);
	return sample;
}

float cOscillator::SawSample(){ return 0.0f; }
float cOscillator::SquareSample(){ return 0.0f; }
float cOscillator::TriangleSample(){ return 0.0f; }
float cOscillator::WhiteSample(){ return 0.0f; }

void cOscillator::SetFrequency(float frequency)
{
	mFrequency = frequency; 
	mIncrement = (2 * M_PI * mFrequency) / mSampleRate; 
}