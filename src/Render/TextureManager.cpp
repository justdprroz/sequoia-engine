#include "Render/TextureManager.hpp"


TextureManager::TextureManager()
{
}

TextureManager::TextureManager(std::string assets_path)
{
    assets_path_ = assets_path;
    LoadBlockTileset();
    LoadEntityTileset();
    LoadCharacters();
}

void TextureManager::SetAssetsPath(std::string path)
{
    assets_path_ = path;
}

void TextureManager::LoadBlockTileset()
{
    block_tileset_.loadFromFile(assets_path_ + "/textures/tiles/tileset.png");
}

void TextureManager::LoadEntityTileset()
{
    entity_tileset_.loadFromFile(assets_path_ + "/textures/entity/characters_tileset.png");
}

void TextureManager::LoadCharacters()
{
    for (int i = 0; i < 16; i++)
    {
        characters_textures_[i] = sf::Texture();
        characters_textures_[i].loadFromFile(assets_path_ + "/textures/entity/characters/" + std::to_string(i) + ".png");
    }
}

sf::Texture *TextureManager::GetBlockTilesetPtr()
{
    return &block_tileset_;
}

sf::Texture *TextureManager::GetEntityTilesetPtr()
{
    return &entity_tileset_;
}

sf::Texture *TextureManager::GetCharacterTexturePtr(int id)
{
    return &characters_textures_[id];
}
