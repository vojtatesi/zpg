#pragma once
#include <memory>
#include "Texture.h"
#include <unordered_map>

class TextureManager {
public:

	enum class ModelType {
		Formula,
		Cube,
		House,
		Fiona,
		Shrek,
		Toilet,
		Grass,
		SkyboxGrass
	};

    static std::shared_ptr<Texture> get(ModelType type);
private:
    static std::unordered_map<std::string, std::weak_ptr<Texture>> cache;
	static const std::unordered_map<ModelType, std::string> texturePaths;
};

