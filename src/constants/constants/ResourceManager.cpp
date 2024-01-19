#include "ResourceManager.h"

namespace constants
{
    // Initialize static member variables
    std::unordered_map<std::string, sf::Texture> ResourceManager::textureMap;

    const sf::Texture& ResourceManager::getTexture (const std::string& relativePath)
    {
        auto iterator = textureMap.find(relativePath);

        // If the texture is not found, we have to load the value and store it.
        if (iterator == textureMap.end())
        {
            textureMap[relativePath].loadFromFile(relativePath);
            return textureMap[relativePath];
        }
        // Else, just return the value that is already in the map.
        return iterator->second;
    }
}