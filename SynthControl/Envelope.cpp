#include "Envelope.h"

cEnvelope::cEnvelope(uint32_t attack, uint32_t decay, uint32_t sustain, uint32_t release, float attackGain, float decayGain)
	: mAttackDuration(attack), mDecayDuration(decay), mSustainDuration(sustain), mReleaseDuration(release), mAttackTargetGain(attackGain), mDecayTargetGain(decayGain)
{}

const float cEnvelope::operator[](std::size_t idx) const
{
	if (idx < mAttackDuration)
	{
		return mAttackTargetGain * ((float)idx / (float)mAttackDuration);
	}

	if (idx < mAttackDuration + mDecayDuration)
	{
		float gainRange = mAttackTargetGain - mDecayTargetGain;
		float position = (float)(idx - mAttackDuration) / mDecayDuration;
		return mAttackTargetGain - (position * gainRange);
	}

	if (idx < mAttackDuration + mDecayDuration + mSustainDuration)
		return mDecayTargetGain;

	if (idx < mAttackDuration + mDecayDuration + mSustainDuration + mReleaseDuration)
	{
		float position = (float)(idx - (mAttackDuration + mDecayDuration + mSustainDuration)) / mReleaseDuration;
		return mDecayTargetGain - (position * mDecayTargetGain);
	}

	return 0.0;
}