#pragma once

#include <engine/Component.h>
#include <AL/al.h>

namespace GameEngine {

	class Transform;
	class Sound;

	class AudioSource : public GameEngine::Component {
	
	private:
		Transform* trans;
		ALuint buffer;
		ALuint source;

	protected:
	public:
		AudioSource(Sound* _snd) {
			alGenBuffers((ALuint)1, &buffer);
			alGenSources((ALuint)1, &source);
			alSourcef(source, AL_PITCH, 1);
			alSourcef(source, AL_GAIN, 1);
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
		};

		void Play() {
			alSourcePlay(source);
		};

		void Destroy() { delete this; }

		~AudioSource() {
			alDeleteSources(1, &source);
			alDeleteBuffers(1, &buffer);
		}

	};

}
