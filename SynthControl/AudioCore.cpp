#include "AudioCore.h"
#include <SDL.h>
#include <cstdio>
#include <cmath>
#include "SineGenerator.h"
#include "SawGenerator.h"


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
	: mBiquad(cBiquad::eBiquadType::LPF, 48000, 300), mBiquad1(cBiquad::eBiquadType::LPF, 48000, 150), mDelay(12000), mMeterIndex(0), mPan(0.5f)
{
	for(uint32_t i = 0; i < 12; i++)
	{
		mGenerators[i] = new cSineGenerator();
		mGenerators[i]->SetSampleRate(48000);
		mGenerators[i]->SetFrequency(pitch[i]);
		
		mGeneratorType[i] = false;

		mGain[i] = 0.0f;
		mMute[i] = true;
	}
	OpenAudioDevice();
}

cAudioCore::~cAudioCore()
{
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
	
	if(!mGeneratorType[oscillator])
	{
		generator = new cSawGenerator();
	}
	else
	{
		generator = new cSineGenerator();
	}

	generator->SetSampleRate(48000);
	generator->SetFrequency(pitch[oscillator]);

	mGenerators[oscillator] = generator;

	mGeneratorType[oscillator] = !mGeneratorType[oscillator];
}

void cAudioCore::MuteOscillators(bool mute, int oscillator)
{
	mMute[oscillator] = mute;
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
			sample += ((mGenerators[i]->NextSample() * mGain[i]));
	}

	float DelaySample = mDelay.ReadSample();

	sample += (DelaySample * 0.25);

	mDelay.WriteSample(sample);
	
	sSample stereoSample;
	stereoSample.left = sample * sqrtf(1.0f - mPan);
	stereoSample.right = sample * sqrtf(mPan);

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
	audioSpecDesired.samples = 512;

	SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &audioSpecDesired, &audioSpecActual, SDL_AUDIO_ALLOW_ANY_CHANGE);
	int NumberOFDevices = SDL_GetNumAudioDevices(0);
	for (int i = 0; i < NumberOFDevices; i++)
		printf("Audio device %d: %s\r\n", i, SDL_GetAudioDeviceName(i, 0));
	if (device == 0)
	{
		printf("Failed to open audio: %s\n", SDL_GetError());
	}
	else
	{
		printf("opened Audio device %d: %s", device, SDL_GetAudioDeviceName(device, 0));
	}
	SDL_PauseAudioDevice(device, 0);
}

float cAudioCore::GetMeterValue(int meter) const
{
	float sum = 0.0f;
	for (uint32_t i = 0; i < MeterBufferLength; i++)
	{
		sum += mMeterBuffer[meter][i] * mMeterBuffer[meter][i];
	}

	sum /= MeterBufferLength;

	return sqrtf(sum);
}

