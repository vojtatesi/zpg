#pragma once
#include <memory>
#include "Scene.h"
#include "ShaderProgram.h"

class SceneBuilder
{

public:
	static std::shared_ptr<Scene> createSolarSystemScene(const std::shared_ptr<ShaderProgram>& phongShader, const std::shared_ptr<ShaderProgram>& constantShader);
	static std::shared_ptr<Scene> createTriangleScene(const std::shared_ptr<ShaderProgram>& shader);
	static std::shared_ptr<Scene> createSpheresScene(const std::shared_ptr<ShaderProgram>& basicShader);
	static std::shared_ptr<Scene> createComplexScene(const std::shared_ptr<ShaderProgram>& phongShader, const std::shared_ptr<ShaderProgram>& constantShader);
	static std::shared_ptr<Scene> createShaderTestScene(const std::shared_ptr<ShaderProgram>& phongShader, const std::shared_ptr<ShaderProgram>& constantShader,
		const std::shared_ptr<ShaderProgram>& lambertShader, const std::shared_ptr<ShaderProgram>& blinnShader);
};
