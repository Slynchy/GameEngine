
#include "Audio.h"
#include <exception>

GameEngine::Audio::Audio() {
	device = alcOpenDevice(NULL);
	if (!device) {
		throw std::exception("durrr"); // fixme
	}

	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	if (!supportsEnumeration()) {
		throw std::exception("durrrrrrrr"); // fixme
	}

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)) {
		throw std::exception("durrrrrrrrrrrrrrrrr"); // fixme
	}
}

GameEngine::Audio::~Audio() {
	// We can use this to get the full device list
	// but we just want whatever the OS default is.
		//device = alcGetContextsDevice(context);

	alcMakeContextCurrent(0);
	alcDestroyContext(context);
	alcCloseDevice(device);
}