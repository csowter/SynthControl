#ifndef biquad_h
#define biquad_h

class cBiquad
{
public:
	enum eBiquadType
	{
		LPF,
		HPF
	};
private:
	eBiquadType mType;
	float mA0;
	float mA1;
	float mA2;
	float mB0;
	float mB1;
	float mB2;

	int mSampleRate;
	float mCutoff;
	float mOmega;
	float mAlpha;
	float mBeta;

	void CalculateCoefficients();

public:
	cBiquad(eBiquadType type, int sampleRate, float cutoff);
	float NextSample(float sampleIn);
};

#endif