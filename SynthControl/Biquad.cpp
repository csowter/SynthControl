#include "Biquad.h"

cBiquad::cBiquad(eBiquadType type, int sampleRate, float cutoff)
	:mType(type), mSampleRate(sampleRate), mCutoff(cutoff)
{

}

float cBiquad::NextSample(float sampleIn)
{
	return 0.0f;
}

void cBiquad::CalculateCoefficients()
{
	switch(mType)
	{
	case LPF:
		break;
	case HPF:
		break;
	}

}