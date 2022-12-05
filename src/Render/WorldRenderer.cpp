#include "Render/WorldRenderer.hpp"

#include <chrono>


// ! Debug stuff; CREATE LOGGER / INFORMATION POOL
int RENDERED_VERTICES = 0;

void WorldRenderer::Update(World &world, TextureManager &texture_manager)
{
    int vertices_count = world.GetChunks().size() * kChunkSize * kChunkSize;
    tile_floor_vertices_.setPrimitiveType(sf::Quads);
    tile_floor_vertices_.resize(vertices_count * 4);
    tile_wall_vertices_.setPrimitiveType(sf::Quads);
    tile_wall_vertices_.resize(vertices_count * 4);

    tile_atlas_ = texture_manager.GetBlockTilesetPtr();

    int current_index = 0;

    for (auto &chunks_entry : world.GetChunks())
    {
        auto &blocks = chunks_entry.second.GetBlocks();
        auto chunk_origin = chunks_entry.second.GetOrigin();
        for (int y = 0; y < kChunkSize; y++) // "Y" coord
        {
            for (int x = 0; x < kChunkSize; x++) // "X" coord
            {
                int id = blocks[y][x].GetId();       // Id of current block
                int biome = blocks[y][x].GetBiome(); // Biome of current block

                int gX = chunk_origin.x * kChunkSize + x; // Global X coordinate of current block
                int gY = chunk_origin.y * kChunkSize + y; // Global Y coordinate of current block

                int sX = 0, sY = 0, woX = 0, woY = 0, toX = 0, toY = 0; // size X, size Y, world offset X, world offset Y, texture offset X, texture offset Y

                int layer_type = 1;

                if (id == 0) // path
                {
                    layer_type = 0;
                    sX = 1, sY = 1;
                    woX = x, woY = y;
                    toX = 4;
                    toY = 0 + mod((gY * 281 + gX * 491) % 89, 4);
                }
                else if (id == 1) // grass
                {
                    layer_type = 0;
                    sX = 1, sY = 1;
                    woX = x, woY = y;
                    toX = 0;
                    toY = 1 + mod((gY * 281 + gX * 491) % 89, 4);
                }
                else if (id == 2) // water
                {
                    layer_type = 0;
                    sX = 1, sY = 1;
                    woX = x, woY = y;
                    toX = 19;
                    toY = 13;
                }
                else if (id == 3) // tree
                {
                    sX = 5, sY = 6;
                    woX = x - 2, woY = y - 5;
                    toX = 0, toY = 6;
                }
                else if (id == 4) // decor_stone_small_1
                {
                    sX = 1, sY = 1;
                    woX = x, woY = y;
                    toX = 7;
                    toY = 0;
                }
                else if (id == 5) // decor_stone_small_2
                {
                    sX = 1, sY = 1;
                    woX = x, woY = y;
                    toX = 8;
                    toY = 0;
                }
                else if (id == 6) // decor_flower_1
                {
                    sX = 1, sY = 1;
                    woX = x, woY = y;
                    toX = 8;
                    toY = 7;
                }
                else if (id == 7) // decor_flower_2
                {
                    sX = 1, sY = 2;
                    woX = x, woY = y - 1;
                    toX = 7;
                    toY = 7;
                }
                else if (id == 8) // decor_flower_3
                {
                    sX = 1, sY = 1;
                    woX = x, woY = y;
                    toX = 8;
                    toY = 8;
                }
                else if (id == 9) // decor_flower_4
                {
                    sX = 1, sY = 1;
                    woX = x, woY = y;
                    toX = 6, toY = 9;
                }
                else if (id == 10) // decor_flower_5
                {
                    sX = 1, sY = 1;
                    woX = x, woY = y;
                    toX = 7, toY = 9;
                }
                else if (id == 11) // decor_flower_6
                {
                    sX = 1, sY = 1;
                    woX = x, woY = y;
                    toX = 8, toY = 9;
                }
                else if (id == 12) // big_stone
                {
                    sX = 2, sY = 2;
                    woX = x, woY = y - 1;
                    toX = 5, toY = 0;
                }
                else if (id == 13) // small_tree_trunk
                {
                    sX = 2, sY = 2;
                    woX = x, woY = y - 1;
                    toX = 5, toY = 2;
                }
                else if (id == 14) // vertical_trunk
                {
                    sX = 2, sY = 3;
                    woX = x, woY = y - 2;
                    toX = 7, toY = 1;
                }
                else if (id == 15) // horizontal_trunk
                {
                    sX = 3, sY = 2;
                    woX = x, woY = y - 1;
                    toX = 6, toY = 4;
                }
                else if (id == 16) // rabbit_hole
                {
                    sX = 2, sY = 1;
                    woX = x, woY = y;
                    toX = 7, toY = 6;
                }
                else if (id == 17) // bush
                {
                    sX = 2, sY = 2;
                    woX = x, woY = y - 1;
                    toX = 5, toY = 7;
                }
                else
                {
                    std::cout << id << "\n";
                }
                toX += biome * 21;

                // current_index
                sf::Vertex *quad;
                if (layer_type == 0)
                {
                    quad = &tile_floor_vertices_[(current_index++) * 4];
                }
                else if (layer_type == 1)
                {
                    quad = &tile_wall_vertices_[(current_index++) * 4];
                }
                else
                {
                    std::cerr << "!!!!Wrong block at: " << gX << " " << gY << "\n";
                }

                int coX = chunk_origin.x * kChunkSize * TILE_SIZE, coY = chunk_origin.y * kChunkSize * TILE_SIZE;
                quad[0].position = sf::Vector2f(coX + woX * TILE_SIZE, coY + woY * TILE_SIZE);
                quad[1].position = sf::Vector2f(coX + (woX + sX) * TILE_SIZE, coY + woY * TILE_SIZE);
                quad[2].position = sf::Vector2f(coX + (woX + sX) * TILE_SIZE, coY + (woY + sY) * TILE_SIZE);
                quad[3].position = sf::Vector2f(coX + woX * TILE_SIZE, coY + (woY + sY) * TILE_SIZE);

                quad[0].texCoords = sf::Vector2f(toX * TEXTURE_SIZE, toY * TEXTURE_SIZE);
                quad[1].texCoords = sf::Vector2f((toX + sX) * TEXTURE_SIZE, toY * TEXTURE_SIZE);
                quad[2].texCoords = sf::Vector2f((toX + sX) * TEXTURE_SIZE, (toY + sY) * TEXTURE_SIZE);
                quad[3].texCoords = sf::Vector2f(toX * TEXTURE_SIZE, (toY + sY) * TEXTURE_SIZE);
            }
        }
    }

    entity_vertices_.setPrimitiveType(sf::Quads);
    entity_vertices_.resize(world.GetEntities().size() * 4);
    int index = 0;
    for (auto entity : world.GetEntities())
    {

        sf::Vertex *quad = &entity_vertices_[index * 4];
        sf::Vector2f pos = entity->GetPosition();

        int type = entity->GetType();
        int id = entity->GetId();
        int state = entity->GetState();
        int heading = entity->GetHeading();
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
        int frame = ms.count() / (1250 / entity->GetSpeed()) % 4;

        entity_atlas_ = texture_manager.GetCharacterTexturePtr(id);

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
}
void WorldRenderer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    RENDERED_VERTICES = tile_floor_vertices_.getVertexCount() + tile_wall_vertices_.getVertexCount();
    states.transform *= getTransform();
    states.texture = tile_atlas_;
    target.draw(tile_floor_vertices_, states);
    target.draw(tile_wall_vertices_, states);
    states.texture = entity_atlas_;
    target.draw(entity_vertices_, states);
};