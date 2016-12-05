#ifndef envelope_h
#define envelope_h

#include <cstddef>
#include <cstdint>

class cEnvelope
{
private:
	//duration in samples
	uint32_t mAttackDuration;
	uint32_t mDecayDuration;
	uint32_t mSustainDuration;
	uint32_t mReleaseDuration;

	float mAttackTargetGain;
	float mDecayTargetGain;

public:
	cEnvelope() = delete;
	cEnvelope(uint32_t attack, uint32_t decay, uint32_t sustain, uint32_t release, float attackGain, float decayGain);
	const float operator[](std::size_t idx) const;
};

#endif