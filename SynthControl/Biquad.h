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
	float mA3;
	float mA4;
	float mA5;

	float mX1;
	float mX2;
	float mY1;
	float mY2;

	float mFrequency;
	int mSampleRate;

	void CalculateCoefficients();
	void CalculateLPFCoefficients();
	void CalculateHPFCoefficients();

public:
	cBiquad(eBiquadType type, int sampleRate, float cutoff);
	float NextSample(float sampleIn);
};

#endif