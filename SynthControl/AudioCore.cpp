#include "AudioCore.h"
#include <SDL.h>
#include <cstdio>
#include <cmath>
#include "SineGenerator.h"
#include "SawGenerator.h"
#include "SquareGenerator.h"

float pitch[] =
{
	261.63f,
	277.18f,
	293.66f,
	311.13f,
	329.63f,
	349.23f,
	369.99f,
	392.00f,
	415.30f,
	440.0f,
	466.16f,
	493.88f
};

cAudioCore::cAudioCore()
	: mBiquad(cBiquad::eBiquadType::LPF, 48000, 300), mBiquad1(cBiquad::eBiquadType::LPF, 48000, 150), mMeterIndex(0), mPan(0.5f), mDelayGain(0.25f), mDelayTargetGain(0.25f), mEnvelope(480, 480, 200, 200, 0.8, 0.4)
{
	mDelay[0].SetDelayLength(24000);
	mDelay[1].SetDelayLength(24000);
	for(uint32_t i = 0; i < 12; i++)
	{
		mGenerators[i] = new cSquareGenerator();
		mGenerators[i]->SetSampleRate(48000);
		mGenerators[i]->SetFrequency(pitch[i]);
		
		mGeneratorType[i] = square;

		mGain[i] = 0.0f;
		mMute[i] = true;
	}
	OpenAudioDevice();
}

cAudioCore::~cAudioCore()
{
	SDL_PauseAudioDevice(mAudioDevice, 1);
	SDL_CloseAudioDevice(mAudioDevice);
	for (uint32_t i = 0; i < 12; i++)
	{
		iGenerator *generator = mGenerators[i];
		mGenerators[i] = nullptr;
		delete generator;
	}
}

void cAudioCore::SwitchOscillator(int oscillator)
{
	bool mute;
	iGenerator *generator = mGenerators[oscillator];
	mGenerators[oscillator] = nullptr;
	delete generator;
	
	switch (mGeneratorType[oscillator])
	{
	case sine:
		generator = new cSquareGenerator();
		mGeneratorType[oscillator] = square;
		break;
	case square:
		generator = new cSawGenerator();
		mGeneratorType[oscillator] = saw;
		break;
	case saw:
		generator = new cSineGenerator();
		mGeneratorType[oscillator] = sine;
		break;
	}

	generator->SetSampleRate(48000);
	generator->SetFrequency(pitch[oscillator]);

	mGenerators[oscillator] = generator;
}

void cAudioCore::MuteOscillators(bool mute, int oscillator)
{
	mMute[oscillator] = mute;
	mEnvelopeSample = 0;
}

void cAudioCore::SetGain(int oscillator, float gain)
{
	mTargetGain[oscillator] = gain;
}

static void audioCallback(void *userData, Uint8 *audioStream, int len)
{
	cAudioCore *audioCore = (cAudioCore *)userData;
	
	float *floatStream = (float *)audioStream;
	for (int i = 0; i <( len / sizeof(float)) / 2; i++)
	{
		cAudioCore::sSample sample = audioCore->NextSample();
		*floatStream = sample.left;
		floatStream++;
		*floatStream = sample.right;
		floatStream++;
	}
}

cAudioCore::sSample cAudioCore::NextSample()
{
	float sample = 0.0f;
	for (uint32_t i = 0; i < 12; i++)
	{
		if (!mMute[i])
		{
			if (mGain[i] < mTargetGain[i])
				mGain[i] += 0.0002f;
			else if (mGain[i] > mTargetGain[i])
				mGain[i] -= 0.0002f;
		}
		else
		{
			if (mGain[i] > 0.0f)
				mGain[i] -= 0.0002f;
		}

		if (mGenerators[i] != nullptr)
			sample += (mGenerators[i]->NextSample() * mGain[i]);// *mEnvelope[mEnvelopeSample]);
	}

	mEnvelopeSample++;
		
	sSample stereoSample;
	stereoSample.left = sample;
	stereoSample.right = sample;

	if (mDelayGain < mDelayTargetGain)
		mDelayGain += 0.0002f;
	else if (mDelayGain > mDelayTargetGain)
		mDelayGain -= 0.0002f; 

	stereoSample.left += (mDelay[0].ReadSample() * mDelayGain);
	stereoSample.right += (mDelay[1].ReadSample() * mDelayGain);

	stereoSample.left = stereoSample.left * sqrtf(1.0f - mPan);
	stereoSample.right = stereoSample.right * sqrtf(mPan);

	mDelay[0].WriteSample(stereoSample.left);
	mDelay[1].WriteSample(stereoSample.right);

	mMeterBuffer[0][mMeterIndex] = stereoSample.left;
	mMeterBuffer[1][mMeterIndex] = stereoSample.right;
	mMeterIndex++;
	mMeterIndex &= (MeterBufferLength - 1);

	return stereoSample;
}

void cAudioCore::OpenAudioDevice()
{
	SDL_AudioSpec audioSpecDesired;
	SDL_AudioSpec audioSpecActual;

	audioSpecDesired.freq = 48000;
	audioSpecDesired.format = AUDIO_F32;
	audioSpecDesired.channels = 2;
	audioSpecDesired.callback = audioCallback;
	audioSpecDesired.userdata = this;
	audioSpecDesired.samples = 1024;

	mAudioDevice = SDL_OpenAudioDevice(NULL, 0, &audioSpecDesired, &audioSpecActual, SDL_AUDIO_ALLOW_ANY_CHANGE);
	int NumberOFDevices = SDL_GetNumAudioDevices(0);
	for (int i = 0; i < NumberOFDevices; i++)
		printf("Audio device %d: %s\r\n", i, SDL_GetAudioDeviceName(i, 0));
	if (mAudioDevice == 0)
	{
		printf("Failed to open audio: %s\n", SDL_GetError());
	}
	else
	{
		printf("opened Audio device %d: %s", mAudioDevice, SDL_GetAudioDeviceName(mAudioDevice, 0));
	}
	SDL_PauseAudioDevice(mAudioDevice, 0);
}

float cAudioCore::GetMeterValue(int meter) const
{
	float sum = 0.0f;
	for (uint32_t i = 0; i < MeterBufferLength; i++)
	{
		sum += fabs(mMeterBuffer[meter][i]) * fabs(mMeterBuffer[meter][i]);
	}

	sum /= MeterBufferLength;

	return sqrtf(sum);
}

