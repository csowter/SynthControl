#ifndef generator_h
#define generator_h

#include <cstdint>

class iGenerator
{
public:
	virtual float NextSample() = 0;
	virtual void SetSampleRate(uint32_t sampleRate) = 0;
	virtual void SetFrequency(float frequency) = 0;
	virtual void SetMute(bool mute) = 0;
	virtual bool GetMute() = 0;
};

#endif