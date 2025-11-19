#include "TextureManager.h"
#include <iostream>

std::unordered_map<std::string, std::weak_ptr<Texture>> TextureManager::cache;

const std::unordered_map<TextureManager::ModelType, std::string> TextureManager::texturePaths = {
    { ModelType::Fiona,   "../Textures/fiona.png" },
    { ModelType::Shrek,   "../Textures/shrek.png" },
    { ModelType::Toilet,  "../Textures/toiled.jpg" },
    { ModelType::Grass,  "../Textures/grass.png" },
    { ModelType::SkyboxGrass,  "../Textures/negy.jpg" }
};

std::shared_ptr<Texture> TextureManager::get(ModelType type)
{   
    auto it = texturePaths.find(type);
    if (it == texturePaths.end()) {
        throw std::runtime_error("Model path not found for requested type.");
    }

    const std::string& path = it->second;

    if (auto existing = cache[path].lock()) {        
        return existing;
    }
   
    auto tex = std::make_shared<Texture>();
    if (!tex->loadFromFile(path)) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return nullptr;
    }
    
    cache[path] = tex;
    return tex;
}
