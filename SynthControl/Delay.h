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

	void ZeroBuffer();

public:
	cDelay();
	cDelay(uint32_t delayLength);
	~cDelay();

	float ReadSample();
	void WriteSample(float sampleIn);
	void SetDelayLength(uint32_t size);
};

#endif