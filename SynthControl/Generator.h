#ifndef generator_h
#define generator_h

#include <cstdint>

class iGenerator
{
public:
	virtual float NextSample() = 0;
	virtual void SetSampleRate(uint32_t sampleRate) = 0;
	virtual void SetFrequency(float frequency) = 0;
};

#endif