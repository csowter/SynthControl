#ifndef oscillator_h
#define oscillator_h

class cOscillator
{
public:
	enum eType
	{
		Sine,
		Saw,
		Square,
		Triangle,
		White
	};
	cOscillator();
	cOscillator(float frequency, int sampleRate, cOscillator::eType type);
	float NextSample();
	void SetType(cOscillator::eType type);

	void SetSampleRate(int sampleRate) { mSampleRate = sampleRate; }
	void SetFrequency(float frequency);
	void SetMute(bool mute){ mMute = mute; }
private:
	float mFrequency;
	int mSampleRate;
	eType mType;
	float mIncrement;
	float mSum;
	bool mMute;

	float SineSample();
	float SawSample();
	float SquareSample();
	float TriangleSample();
	float WhiteSample();
};

#endif