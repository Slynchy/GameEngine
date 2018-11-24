#include "AudioSource.h"
#include <AL/alc.h>
#include <engine/Sound.h>

static inline ALenum to_al_format(short channels, short samples)
{
	bool stereo = (channels > 1);

	switch (samples) {
	case 16:
		if (stereo)
			return AL_FORMAT_STEREO16;
		else
			return AL_FORMAT_MONO16;
	case 8:
		if (stereo)
			return AL_FORMAT_STEREO8;
		else
			return AL_FORMAT_MONO8;
	default:
		return -1;
	}
}

void GameEngine::AudioSource::Init(std::shared_ptr<Sound> _snd) {
	alGenBuffers((ALuint)1, &buffer);
	alGenSources((ALuint)1, &source);
	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);

	/// @todo Add position data from this->trans ptr
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);

	alSourcei(source, AL_LOOPING, AL_FALSE);

	alBufferData(
		buffer,
		_snd->format,
		_snd->data,
		_snd->size,
		_snd->freq
	);

	alSourcei(source, AL_BUFFER, buffer);
}

GameEngine::AudioSource::AudioSource(std::shared_ptr<Sound> _snd) {
	this->Init(_snd);
}

void GameEngine::AudioSource::Play() {
	alSourcePlay(source);
};

GameEngine::AudioSource::~AudioSource() {
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
}
