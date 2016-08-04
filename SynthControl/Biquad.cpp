#include "Biquad.h"
#define _USE_MATH_DEFINES
#include <cmath>

cBiquad::cBiquad(eBiquadType type, int sampleRate, float frequency)
	:mType(type), mSampleRate(sampleRate), mFrequency(frequency)
{
	CalculateCoefficients();
}

float cBiquad::NextSample(float sampleIn)
{
	float result;

	/* compute result */
	result = mA0 * sampleIn + mA1 * mX1 + mA2 * mX2 -
		mA3 * mY1 - mA4 * mY2;

	/* shift x1 to x2, sample to x1 */
	mX2 = mX1;
	mX1 = sampleIn;

	/* shift y1 to y2, result to y1 */
	mY2 = mY1;
	mY1 = result;

	return result;
}

void cBiquad::CalculateCoefficients()
{
	switch(mType)
	{
	case LPF:
		CalculateLPFCoefficients();
		break;
	case HPF:
		CalculateHPFCoefficients();
		break;
	}
}

void cBiquad::CalculateLPFCoefficients()
{
	float A, omega, sn, cs, alpha, beta;
	float a0, a1, a2, b0, b1, b2;

	float dbGain = 4.0f;
	float bandwidth = 10.0f;

	A = pow(10, dbGain / 40);
	omega = 2 * M_PI * mFrequency / mSampleRate;
	sn = sin(omega);
	cs = cos(omega);
	alpha = sn * sinh(M_LN2 / 2 * bandwidth * omega / sn);
	beta = sqrt(A + A);

	b0 = (1 - cs) / 2;
	b1 = 1 - cs;
	b2 = (1 - cs) / 2;
	a0 = 1 + alpha;
	a1 = -2 * cs;
	a2 = 1 - alpha;

	mA0 = b0 / a0;
	mA1 = b1 / a0;
	mA2 = b2 / a0;
	mA3 = a1 / a0;
	mA4 = a2 / a0;

	/* zero initial samples */
	mX1 = mX2 = 0;
	mY1 = mY2 = 0;
}

void cBiquad::CalculateHPFCoefficients()
{
	float A, omega, sn, cs, alpha, beta;
	float a0, a1, a2, b0, b1, b2;

	float dbGain = 40.0f;
	float bandwidth = 10.0f;

	A = pow(10, dbGain / 40);
	omega = 2 * M_PI * mFrequency / mSampleRate;
	sn = sin(omega);
	cs = cos(omega);
	alpha = sn * sinh(M_LN2 / 2 * bandwidth * omega / sn);
	beta = sqrt(A + A);

	b0 = (1 + cs) / 2;
	b1 = -(1 + cs);
	b2 = (1 + cs) / 2;
	a0 = 1 + alpha;
	a1 = -2 * cs;
	a2 = 1 - alpha;

	mA0 = b0 / a0;
	mA1 = b1 / a0;
	mA2 = b2 / a0;
	mA3 = a1 / a0;
	mA4 = a2 / a0;

	/* zero initial samples */
	mX1 = mX2 = 0;
	mY1 = mY2 = 0;
}
