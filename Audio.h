#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <exception>

namespace GameEngine {

	class Audio {

	private:
		ALCdevice *device;
		ALboolean enumeration;
		ALCcontext *context;

	protected:
	public:
		Audio() {
			device = alcOpenDevice(NULL);
			if (!device) {
				throw std::exception("durrr");
			}

			enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
			if (!supportsEnumeration()){

			}

			context = alcCreateContext(device, NULL);
			if (!alcMakeContextCurrent(context)) {
				throw std::exception("durrrrrrrrrrrrrrrrr");
			}
		}

		bool supportsEnumeration() {
			return enumeration == AL_TRUE;
		}

		~Audio() {
			//device = alcGetContextsDevice(context);
			alcMakeContextCurrent(NULL);
			alcDestroyContext(context);
			alcCloseDevice(device);
		}

	};

}