#pragma once

#include <engine/Resource.h>
#include <AL/al.h>
#include <alut.h>

namespace GameEngine {

	/// Small class for holding sound resources
	class Sound : public Resource {

	private:

	protected:
	public:
		/// The length of the track in bytes
		ALsizei size; 

		/// The frequency/polling rate/hertz the audio runs at
		ALsizei freq;

		/// Format of the sound
		ALenum format;

		/// Pointer to data 
		ALvoid *data;

		/// Does it loop?
		ALboolean loop = AL_FALSE;

		Sound(const char* path) {
			alutLoadWAVFile((ALbyte*)path, &format, &data, &size, &freq, &loop);
		}

		~Sound() {

		}

	};
}