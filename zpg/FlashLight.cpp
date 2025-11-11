#include "FlashLight.h"
#include "ShaderProgram.h"

void FlashLight::applyToShader(class ShaderProgram* shader, const std::string& base) const
{
	shader->setUniform3f(base + ".position", position);
	shader->setUniform3f(base + ".direction", direction);
	shader->setUniform3f(base + ".color", (enabled ? 1.0f : 0.0f) * color * intensity);
	shader->setUniform1f(base + ".innerCutoff", innerCutoff);
	shader->setUniform1f(base + ".outerCutoff", outerCutoff);
	shader->setUniform1i(base + ".type", static_cast<int>(type));

	setAttenuationUniforms(shader, base);
}