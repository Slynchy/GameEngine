#pragma once

#include <engine/Component.h>
#include <AL/al.h>
#include <memory>

namespace GameEngine {

	class Transform;
	class Sound;

	/// Component class for AudioSources
	class AudioSource : public GameEngine::Component {
	
	private:
		/// Currently unused, not deprecated
		/// @unused
		Transform* trans;

		/// OpenAL index for buffer data
		ALuint buffer;

		/// OpenAL index for the audiosource data
		ALuint source;

	protected:
	public:
		AudioSource(std::shared_ptr<Sound> _snd);

		void Init(std::shared_ptr<Sound> _snd);

		/// Play whatever audio buffer is bound this audiosource
		void Play();

		/// @todo FIXME
		void Destroy() { }

		~AudioSource();

	};

}
