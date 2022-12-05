#ifndef SEQUOIA_ENGINE_SRC_RENDER_TEXTURE_MANAGER_
#define SEQUOIA_ENGINE_SRC_RENDER_TEXTURE_MANAGER_

#include <string>

#include <SFML/Graphics/Texture.hpp>


// Main rendering constants
extern const int TEXTURE_SIZE;
extern const int TILE_SIZE;

// Stores all textures, layers, and everything related to them
// ! IMPLEMENT PROPER ATLASING AND GETTING FOR TEXTURES (EG. ATLAS + HASHMAP)
class TextureManager
{
public:
    // Constructors
    TextureManager();
    TextureManager(std::string assets_path);
    // Loaders
    void SetAssetsPath(std::string path);
    void LoadBlockTileset();
    void LoadEntityTileset();
    void LoadCharacters();
    // Getters
    sf::Texture *GetBlockTilesetPtr();
    sf::Texture *GetEntityTilesetPtr();
    sf::Texture *GetCharacterTexturePtr(int id);

private:
    // Path to directory with assets
    std::string assets_path_;
    // Atlases with textures
    sf::Texture block_tileset_;
    sf::Texture entity_tileset_;
    sf::Texture characters_textures_[16];
};

#endif /* SEQUOIA_ENGINE_SRC_RENDER_TEXTURE_MANAGER_ */
