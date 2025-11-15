#include <memory>
#include <unordered_map>
#include "DrawableObject.h"
#include "Triangle.h"
#include "Square.h"
#include "Sphere.h"
#include "Tree.h"
#include "Bush.h"
#include "Suzi_smooth.h"
#include "Ground.h"
#include "Light.h"
#include "PointLight.h"
#include "FlashLight.h"
#include "OBJModel.h"

class ObjectFactory {
public:
	enum class ModelType {
		Formula,
		Cube,
		House,
		Fiona,
		Shrek,
		Toilet
	};

	static std::shared_ptr<DrawableObject> createTriangle(const std::shared_ptr<ShaderProgram>& shader);
	static std::shared_ptr<DrawableObject> createSquare(const std::shared_ptr<ShaderProgram>& shader);
	static std::shared_ptr<DrawableObject> createGround(const std::shared_ptr<ShaderProgram>& shader);
	static std::shared_ptr<DrawableObject> createSphere(const std::shared_ptr<ShaderProgram>& shader);
	static std::shared_ptr<DrawableObject> createTree(const std::shared_ptr<ShaderProgram>& shader);
	static std::shared_ptr<DrawableObject> createBush(const std::shared_ptr<ShaderProgram>& shader);
	static std::shared_ptr<DrawableObject> createSuziSmooth(const std::shared_ptr<ShaderProgram>& shader);

	static std::shared_ptr<PointLight> createPointLight();
	static std::shared_ptr<FlashLight> createFlashLight();	

	static std::shared_ptr<DrawableObject> createOBJ(ModelType type, const std::shared_ptr<ShaderProgram>& shader);

private:
	static std::unordered_map<std::string, std::weak_ptr<Model>> modelCache;
	static const std::unordered_map<ModelType, std::string> modelPaths;
};
