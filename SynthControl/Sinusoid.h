#ifndef sinusoid_h
#define sinusoid_h

#ifndef M_PI
#define M_PI  (3.14159265)
#endif

class Sinusoid
{
private:
	int mSampleRate;
	float mFrequency;
	float mSum;
	float mIncrement;
	float mPreviousSample;
	float mTargetFrequency;
	bool mMute;
public:
	Sinusoid(){ mSum = 0.0f; }
	Sinusoid(float frequency, int sampleRate);
	float NextSample();
	void SetSampleRate(int sampleRate){ mSampleRate = sampleRate; }
	void SetFrequency(float frequency);
	void SetMute(bool mute) { mMute = mute; }
};

#endif