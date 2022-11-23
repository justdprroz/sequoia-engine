// Copyright 2021-2022 JustDprroz

#include "World/World.hpp"
#include <nlohmann/json.hpp>

extern nlohmann::json data;

World::World() : noise_gen_(0)
{
}

World::World(int seed) : seed_(seed), noise_gen_(seed)
{
}

void World::SetSeed(int seed)
{
    seed_ = seed;
}

std::vector<Entity *> &World::GetEntities()
{
    return entities_;
}

// TODO: add entity management system
void World::SummonEntity(Entity &entity)
{
    entities_.push_back(&entity);
}

Block World::GetBlock(sf::Vector2i position)
{
    sf::Vector2i chunk_position = {div<int>(position.x, kChunkSize), div<int>(position.y, kChunkSize)};
    if (!IsChunkExist(chunk_position))
        return {INT_MIN};
    return chunks_[{chunk_position.x, chunk_position.y}].GetBlock({mod<int>(position.x, kChunkSize), mod<int>(position.y, kChunkSize)});
}

void World::PlaceBlock(sf::Vector2i position, Block &block)
{
    chunks_[{div<int>(position.x, kChunkSize), div<int>(position.y, kChunkSize)}].PlaceBlock({mod<int>(position.x, kChunkSize), mod<int>(position.y, kChunkSize)}, block);
}

bool World::IsChunkExist(sf::Vector2i position)
{
    return chunks_.find({position.x, position.y}) != chunks_.end();
}

Chunk *World::GetChunk(sf::Vector2i position)
{
    if (!IsChunkExist({position.x, position.y}))
    {
        PlaceChunk(position);
        GenerateChunkWIP(position);
    }
    return &chunks_[{position.x, position.y}];
}

void World::PlaceChunk(sf::Vector2i position)
{
    if (IsChunkExist(position))
        return;
    chunks_[{position.x, position.y}] = Chunk(position);
}

// TODO: normal serialization
void World::SaveChunks(std::string file_path)
{
    std::ofstream chunkslist;
    chunkslist.open(file_path + "/chunkslist.tem");
    if (!chunkslist.is_open())
    {
        std::cout << "Failed open " << file_path + "/chunkslist.tem" << '\n';
        return;
    }
    int lcx, lcy;
    for (std::map<std::pair<int, int>, Chunk>::iterator it = chunks_.begin(); it != chunks_.end(); ++it)
    {
        lcx = it->first.first;
        lcy = it->first.second;
        chunkslist.write(reinterpret_cast<char *>(&lcx), sizeof(lcx));
        chunkslist.write(reinterpret_cast<char *>(&lcy), sizeof(lcy));
        it->second.SaveChunk(file_path + "/chunk_" + std::to_string(lcx) + "_" + std::to_string(lcy) + ".tem");
    }
    chunkslist.close();
}

// TODO: normal deserialization
void World::LoadChunks(std::string file_path)
{
    std::ifstream chunkslist;
    chunkslist.open(file_path + "/chunkslist.tem");
    if (!chunkslist.is_open())
    {
        std::cout << "Failed open " << file_path + "/chunkslist.tem" << '\n';
        return;
    }
    int lcx, lcy;
    while (!chunkslist.eof())
    {
        chunkslist.read(reinterpret_cast<char *>(&lcx), sizeof(lcx));
        chunkslist.read(reinterpret_cast<char *>(&lcy), sizeof(lcy));
        chunks_[{lcx, lcy}] = Chunk({lcx, lcy});
        chunks_[{lcx, lcy}].LoadChunk(file_path + "/chunk_" + std::to_string(lcx) + "_" + std::to_string(lcy) + ".tem");
    }
    chunkslist.close();
}

// TODO: Great world generation
// void World::GenerateChunk(sf::Vector2i position)
// {
//     for (int i = 0; i < kChunkSize; i++)
//     {
//         for (int j = 0; j < kChunkSize; j++)
//         {
//             float noiseHeightValue = noise_block_.GetNoise(static_cast<float>(i + position.x * kChunkSize), static_cast<float>(j + position.y * kChunkSize));
//             int blockId = static_cast<int>(LinearInterpolation(noiseHeightValue, -1.f, 1.0f, 0.0f, 2.0f));

//             float noiseBiomeValue = noise_biome_.GetNoise(static_cast<float>(i + position.x * kChunkSize), static_cast<float>(j + position.y * kChunkSize));
//             float biomeInterpolated = LinearInterpolation(noiseBiomeValue, -1.f, 1.0f, 0.0f, 3.0f);

//             int biomeId = 0;
//             if (InRange(biomeInterpolated, 0.0f, 0.5f))
//             {
//                 biomeId = 0;
//             }
//             else if (InRange(biomeInterpolated, 0.5f, 0.9f))
//             {
//                 biomeId = 1;
//             }
//             else if (InRange(biomeInterpolated, 0.9f, 1.1f))
//             {
//                 biomeId = 2;
//             }
//             chunks_[{position.x, position.y}].PlaceBlock({i, j}, {blockId, 0});
//         }
//     }
//     chunks_[{position.x, position.y}].SetGenerated();
// }

void World::GenerateChunkWIP(sf::Vector2i position)
{
    for (int i = 0; i < kChunkSize; i++)
    {
        for (int j = 0; j < kChunkSize; j++)
        {
            float noiseHeightValue = noise_gen_.EvaluateFBM(
                static_cast<float>(i + position.x * kChunkSize + 1'000'000),
                static_cast<float>(j + position.y * kChunkSize + 1'000'000),
                data["AMPLITUDE"],
                data["FREQUENCY"],
                data["OCTAVES"]
            );
            int blockId = static_cast<int>(LinearInterpolation(noiseHeightValue, -1.f, 1.0f, 0.0f, 2.0f));

            float noiseBiomeValue = noise_gen_.noise(static_cast<float>(i + position.x * kChunkSize), static_cast<float>(j + position.y * kChunkSize), 1000.0);
            float biomeInterpolated = LinearInterpolation(noiseBiomeValue, -1.f, 1.0f, 0.0f, 3.0f);

            int biomeId = 0;
            if (InRange(biomeInterpolated, 0.0f, 0.5f))
            {
                biomeId = 0;
            }
            else if (InRange(biomeInterpolated, 0.5f, 0.9f))
            {
                biomeId = 1;
            }
            else if (InRange(biomeInterpolated, 0.9f, 1.1f))
            {
                biomeId = 2;
            }
            chunks_[{position.x, position.y}].PlaceBlock({i, j}, {blockId, 0});
        }
    }
    chunks_[{position.x, position.y}].SetGenerated();
}

void World::NoiseInit()
{
    noise_block_.SetSeed(seed_);
    noise_block_.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
    noise_block_.SetFrequency(0.02);
    noise_block_.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise_block_.SetFractalOctaves(3);

    noise_biome_.SetSeed(seed_);
    noise_biome_.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
    noise_biome_.SetFrequency(0.02);
    noise_biome_.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
    noise_biome_.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);
}