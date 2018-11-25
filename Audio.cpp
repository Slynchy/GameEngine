
#include "Audio.h"
#include <exception>

GameEngine::Audio::Audio() {
	device = alcOpenDevice(NULL);
	if (!device) {
		throw std::exception("Failed to find device"); 
	}

	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	if (!supportsEnumeration()) {
		throw std::exception("Failed to enumerate"); 
	}

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)) {
		throw std::exception("Failed to make context"); 
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