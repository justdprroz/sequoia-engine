// Copyright 2021-2022 JustDprroz

#include "Render/Render.hpp"
#include <chrono>

int RENDERED_VERTICES = 0;

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

void RenderChunk::Update(Chunk &chunk, TextureManager &texture_manager)
{
    vertices_.setPrimitiveType(sf::Quads);
    vertices_.resize(kChunkSize * kChunkSize * 4);
    tileset_ptr_ = texture_manager.GetBlockTilesetPtr();
    sf::Vector2i p_origin = chunk.GetOrigin();
    for (int i = 0; i < kChunkSize; i++)
    {
        for (int j = 0; j < kChunkSize; j++)
        {
            sf::Vertex *quad = &vertices_[(i + j * kChunkSize) * 4];

            int id = chunk.blocks_[i][j].GetId();
            int biome = chunk.blocks_[i][j].GetBiome();

            int g_x = p_origin.x * kChunkSize + i;
            int g_y = p_origin.y * kChunkSize + j;

            int sX = 0, sY = 0, woX = 0, woY = 0, toX = 0, toY = 0;

            if (id == 0) // path
            {
                sX = 1, sY = 1;
                woX = i, woY = j;
                toX = 4;
                toY = 0 + mod((g_y * 281 + g_x * 491) % 89, 4);
            }
            else if (id == 1) // grass
            {
                sX = 1, sY = 1;
                woX = i, woY = j;
                toX = 0;
                toY = 1 + mod((g_y * 281 + g_x * 491) % 89, 4);
            }
            else if (id == 2) // water
            {
                sX = 1, sY = 1;
                woX = i, woY = j;
                toX = 19;
                toY = 13;
            }
            else if (id == 3) // tree
            {
                sX = 5, sY = 6;
                woX = i - 2, woY = j - 5;
                toX = 0, toY = 6;
            }
            else if (id == 4) // decor_stone_small_1
            {
                sX = 1, sY = 1;
                woX = i, woY = j;
                toX = 7;
                toY = 0;
            }
            else if (id == 5) // decor_stone_small_2
            {
                sX = 1, sY = 1;
                woX = i, woY = j;
                toX = 8;
                toY = 0;
            }
            else if (id == 6) // decor_flower_1
            {
                sX = 1, sY = 1;
                woX = i, woY = j;
                toX = 8;
                toY = 7;
            }
            else if (id == 7) // decor_flower_2
            {
                sX = 1, sY = 2;
                woX = i, woY = j - 1;
                toX = 7;
                toY = 7;
            }
            else if (id == 8) // decor_flower_3
            {
                sX = 1, sY = 1;
                woX = i, woY = j;
                toX = 8;
                toY = 8;
            }
            else if (id == 9) // decor_flower_4
            {
                sX = 1, sY = 1;
                woX = i, woY = j;
                toX = 6, toY = 9;
            }
            else if (id == 10) // decor_flower_5
            {
                sX = 1, sY = 1;
                woX = i, woY = j;
                toX = 7, toY = 9;
            }
            else if (id == 11) // decor_flower_6
            {
                sX = 1, sY = 1;
                woX = i, woY = j;
                toX = 8, toY = 9;
            }
            else if (id == 12) // big_stone
            {
                sX = 2, sY = 2;
                woX = i, woY = j - 1;
                toX = 5, toY = 0;
            }
            else if (id == 13) // small_tree_trunk
            {
                sX = 2, sY = 2;
                woX = i, woY = j - 1;
                toX = 5, toY = 2;
            }
            else if (id == 14) // vertical_trunk
            {
                sX = 2, sY = 3;
                woX = i, woY = j - 2;
                toX = 7, toY = 1;
            }
            else if (id == 15) // horizontal_trunk
            {
                sX = 3, sY = 2;
                woX = i, woY = j - 1;
                toX = 6, toY = 4;
            }
            else if (id == 16) // rabbit_hole
            {
                sX = 2, sY = 1;
                woX = i, woY = j;
                toX = 7, toY = 6;
            }
            else if (id == 17) // bush
            {
                sX = 2, sY = 2;
                woX = i, woY = j - 1;
                toX = 5, toY = 7;
            }
            else {
                std::cout << id << "\n";
            }
            toX += biome * 21;

            quad[0].position = sf::Vector2f(woX * TILE_SIZE, woY * TILE_SIZE);
            quad[1].position = sf::Vector2f((woX + sX) * TILE_SIZE, woY * TILE_SIZE);
            quad[2].position = sf::Vector2f((woX + sX) * TILE_SIZE, (woY + sY) * TILE_SIZE);
            quad[3].position = sf::Vector2f(woX * TILE_SIZE, (woY + sY) * TILE_SIZE);

            quad[0].texCoords = sf::Vector2f(toX * TEXTURE_SIZE, toY * TEXTURE_SIZE);
            quad[1].texCoords = sf::Vector2f((toX + sX) * TEXTURE_SIZE, toY * TEXTURE_SIZE);
            quad[2].texCoords = sf::Vector2f((toX + sX) * TEXTURE_SIZE, (toY + sY) * TEXTURE_SIZE);
            quad[3].texCoords = sf::Vector2f(toX * TEXTURE_SIZE, (toY + sY) * TEXTURE_SIZE);
        }
    }
    setPosition(chunk.GetOrigin().x * kChunkSize * TILE_SIZE, chunk.GetOrigin().y * kChunkSize * TILE_SIZE);
}

// Draw Chunk
void RenderChunk::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    RENDERED_VERTICES += vertices_.getVertexCount();
    states.transform *= getTransform();
    states.texture = tileset_ptr_;
    target.draw(vertices_, states);
}

void RenderEntity::Update(Entity *entity, TextureManager &texture_manager)
{
    vertices_.setPrimitiveType(sf::Quads);
    vertices_.resize(4);

    sf::Vertex *quad = &vertices_[0];
    sf::Vector2f pos = entity->GetPosition();

    int type = entity->GetType();
    int id = entity->GetId();
    int state = entity->GetState();
    int heading = entity->GetHeading();
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());
    int frame = ms.count() / (1250 / entity->GetSpeed()) % 4;

    tileset_ptr_ = texture_manager.GetCharacterTexturePtr(id);

    int tx = 0;
    int ty = 0;

    if (state == 0)
    {
        ty = 0;
    }

    if (state == 1)
    {
        ty = 0 + frame;
    }

    if (heading == 0)
    {
        tx = 1;
    }
    if (heading == 1)
    {
        tx = 3;
    }
    if (heading == 2)
    {
        tx = 0;
    }
    if (heading == 3)
    {
        tx = 2;
    }

    quad[0].position = sf::Vector2f(pos.x * TILE_SIZE, pos.y * TILE_SIZE);
    quad[1].position = sf::Vector2f((pos.x + 1) * TILE_SIZE, pos.y * TILE_SIZE);
    quad[2].position = sf::Vector2f((pos.x + 1) * TILE_SIZE, (pos.y + 1) * TILE_SIZE);
    quad[3].position = sf::Vector2f(pos.x * TILE_SIZE, (pos.y + 1) * TILE_SIZE);

    quad[0].texCoords = sf::Vector2f(tx * TEXTURE_SIZE, ty * TEXTURE_SIZE);
    quad[1].texCoords = sf::Vector2f((tx + 1) * TEXTURE_SIZE, ty * TEXTURE_SIZE);
    quad[2].texCoords = sf::Vector2f((tx + 1) * TEXTURE_SIZE, (ty + 1) * TEXTURE_SIZE);
    quad[3].texCoords = sf::Vector2f(tx * TEXTURE_SIZE, (ty + 1) * TEXTURE_SIZE);
}

// Draw Entity
void RenderEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    RENDERED_VERTICES += vertices_.getVertexCount();
    states.transform *= getTransform();
    states.texture = tileset_ptr_;
    target.draw(vertices_, states);
};

void RenderWorld::Update(World &world, TextureManager &texture_manager)
{
    for (auto &chunk : world.m_chunks)
    {
        render_chunks_[chunk.first].Update(chunk.second, texture_manager);
    }
    for (int i = 0; i < world.m_entities.size(); i++)
    {
        if (i >= render_entities_.size())
            render_entities_.push_back(RenderEntity());
        render_entities_[i].Update(world.m_entities[i], texture_manager);
    }
}

// Draw Everything
void RenderWorld::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    RENDERED_VERTICES = 0;
    for (auto &render_chunk : render_chunks_)
    {
        render_chunk.second.draw(target, sf::RenderStates(getTransform()));
    }
    for (int i = 0; i < render_entities_.size(); i++)
    {
        render_entities_[i].draw(target, sf::RenderStates(getTransform()));
    }
}