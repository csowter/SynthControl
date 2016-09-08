#ifndef delay_h
#define delay_h

#include <cstdint>

class cDelay
{
private:
	uint32_t mDelayLength;
	uint32_t mInPosition;
	uint32_t mOutPosition;
	float *mDelayBuffer;

public:
	cDelay() = delete;
	cDelay(uint32_t delayLength);
	~cDelay();

	float ReadSample();
	void WriteSample(float sampleIn);
};

#endif