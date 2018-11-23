#pragma once

#include <AL/al.h>
#include <AL/alc.h>

namespace GameEngine {

	/// Pseudo-singleton class used by the engine to power audio
	class Audio {

	private:
		ALCdevice *device;
		ALboolean enumeration;
		ALCcontext *context;

	protected:
	public:
		Audio();

		bool supportsEnumeration() { return enumeration == AL_TRUE; }

		~Audio();

	};

}