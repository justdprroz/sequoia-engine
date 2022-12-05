// Copyright 2021-2022 JustDprroz

#include "World/World.hpp"
#include <nlohmann/json.hpp>

extern nlohmann::json data;

World::World() : m_noise_generator(0), m_rng(0)
{
}

World::World(int seed) : m_seed(seed), m_noise_generator(seed), m_rng(seed)
{
}

void World::SetSeed(int seed)
{
    m_seed = seed;
}

std::vector<Entity *> &World::GetEntities()
{
    return m_entities;
}

// TODO: add entity management system
void World::SummonEntity(Entity &entity)
{
    m_entities.push_back(&entity);
}

Block World::GetBlock(sf::Vector2i position)
{
    sf::Vector2i chunk_position = {div<int>(position.x, kChunkSize), div<int>(position.y, kChunkSize)};
    if (!IsChunkExist(chunk_position))
        return {INT_MIN};
    return m_chunks[{chunk_position.x, chunk_position.y}].GetBlock({mod<int>(position.x, kChunkSize), mod<int>(position.y, kChunkSize)});
}

void World::PlaceBlock(sf::Vector2i position, Block &block)
{
    m_chunks[{div<int>(position.x, kChunkSize), div<int>(position.y, kChunkSize)}].PlaceBlock({mod<int>(position.x, kChunkSize), mod<int>(position.y, kChunkSize)}, block);
}

bool World::IsChunkExist(sf::Vector2i position)
{
    return m_chunks.find({position.x, position.y}) != m_chunks.end();
}

Chunk *World::GetChunk(sf::Vector2i position)
{
    if (!IsChunkExist({position.x, position.y}))
    {
        PlaceChunk(position);
        GenerateChunk(position);
    }
    return &m_chunks[{position.x, position.y}];
}

void World::PlaceChunk(sf::Vector2i position)
{
    if (IsChunkExist(position))
        return;
    m_chunks[{position.x, position.y}] = Chunk(position);
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
    for (std::map<std::pair<int, int>, Chunk>::iterator it = m_chunks.begin(); it != m_chunks.end(); ++it)
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
        m_chunks[{lcx, lcy}] = Chunk({lcx, lcy});
        m_chunks[{lcx, lcy}].LoadChunk(file_path + "/chunk_" + std::to_string(lcx) + "_" + std::to_string(lcy) + ".tem");
    }
    chunkslist.close();
}

// !USED FOR FIXING NON NEGATIVE INPUT FOR NOISE FUNCTION
#define NOISE_OFFSET 1'000'000

void World::GenerateChunk(sf::Vector2i position)
{
    GenerateChunkHeightMap(position);
    GenerateChunkBiomeMap(position);
    GenerateChunkFeatures(position);
    m_chunks[{position.x, position.y}].SetGenerated();
}

void World::GenerateChunkHeightMap(sf::Vector2i position)
{
    for (int i = 0; i < kChunkSize; i++)
    {
        for (int j = 0; j < kChunkSize; j++)
        {
            int current_x = i + position.x * kChunkSize + NOISE_OFFSET;
            int current_y = j + position.y * kChunkSize + NOISE_OFFSET;
            float blockNoise = m_noise_generator.EvaluateFBM(
                static_cast<float>(current_x),
                static_cast<float>(current_y),
                0.0,
                data["AMPLITUDE"],
                data["FREQUENCY"],
                data["OCTAVES"]);
            int blockId = INT_MAX;
            if (blockNoise < 0.2)
            {
                blockId = 2;
            }
            else if (blockNoise < 0.4)
            {
                blockId = 1;
            }
            else if (blockNoise < 0.5)
            {
                blockId = 0;
            }
            else
            {
                blockId = 1;
            }
            m_chunks[{position.x, position.y}].PlaceBlock({i, j}, {blockId, -1});
        }
    }
}

void World::GenerateChunkBiomeMap(sf::Vector2i position)
{
    for (int i = 0; i < kChunkSize; i++)
    {
        for (int j = 0; j < kChunkSize; j++)
        {
            int current_x = i + position.x * kChunkSize + NOISE_OFFSET;
            int current_y = j + position.y * kChunkSize + NOISE_OFFSET;
            int blockId = m_chunks[{position.x, position.y}].GetBlock({i, j}).GetId();

            float noiseBiomeValue = m_noise_generator.EvaluateFBM(
                static_cast<float>(current_x),
                static_cast<float>(current_y),
                1'000'000,
                1.0,
                0.005,
                2);
            int biomeId = INT_MAX;
            if (noiseBiomeValue < 0.6)
            {
                biomeId = 0;
            }
            else if (noiseBiomeValue < 0.8)
            {
                biomeId = 2;
            }
            else
            {
                biomeId = 1;
            }
            m_chunks[{position.x, position.y}].PlaceBlock({i, j}, {blockId, biomeId});
        }
    }
}

void World::GenerateChunkFeatures(sf::Vector2i position)
{
    long long paired_val = pair(position.x, position.y);
    m_rng.seed(paired_val);
    std::uniform_int_distribution dist(0, 1023);
    for (int i = 0; i < kChunkSize; i++)
    {
        for (int j = 0; j < kChunkSize; j++)
        {
            int current_x = i + position.x * kChunkSize + NOISE_OFFSET;
            int current_y = j + position.y * kChunkSize + NOISE_OFFSET;
            int feature_weight = dist(m_rng);
            int blockId = m_chunks[{position.x, position.y}].GetBlock({i, j}).GetId();
            int biomeId = m_chunks[{position.x, position.y}].GetBlock({i, j}).GetBiome();
            if (blockId == 1)
            {
                if (feature_weight <= 10)
                {
                    blockId = 3;
                }
                else if (feature_weight <= (10 + 70))
                {
                    blockId = 3 + (feature_weight - 10) / 5;
                }
            }
            m_chunks[{position.x, position.y}].PlaceBlock({i, j}, {blockId, biomeId});
        }
    }
}