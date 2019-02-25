#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class PostProcessShader {

private:
protected:
	GLuint shaderID;
	bool m_enabled;

public:
	std::string UID;

	PostProcessShader() {
		shaderID = 0;
		UID = "PostProcessShader";
	}

	bool isEnabled() {
		return m_enabled;
	}

	void Disable() {
		m_enabled = false;
	}

	void Enable() {
		m_enabled = true;
	}

	void Toggle() {
		m_enabled = !m_enabled;
	}

	PostProcessShader(GLuint _shaderID) {
		shaderID = _shaderID;
	}

	GLuint getProgramID() {
		return shaderID;
	}

	virtual void Update() {};

};