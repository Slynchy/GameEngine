#pragma once

#include <engine/Resource.h>
#include <AL/al.h>
#include <alut.h>

namespace GameEngine {
	class Sound : public Resource {

	private:

	protected:
	public:
		ALsizei size, freq;
		ALenum format;
		ALvoid *data;
		ALboolean loop = AL_FALSE;

		Sound(const char* path) {
			alutLoadWAVFile((ALbyte*)path, &format, &data, &size, &freq, &loop);
			
		}

		~Sound() {

		}

	};
}