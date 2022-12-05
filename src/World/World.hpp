// Copyright 2021-2022 JustDprroz

#ifndef SEQUOIA_ENGINE_SRC_WORLD_WORLD_
#define SEQUOIA_ENGINE_SRC_WORLD_WORLD_

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstdio>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <SFML/System/Vector2.hpp>
#include <external/FastNoiseLite.h>
#include <Utils.hpp>
#include <climits>
#include <SFML/Window/Event.hpp>
#include <external/noise.hpp>

#include <World/Chunk.hpp>
#include <World/Block.hpp>
#include <World/Entity.hpp>

class World {
public:
    World();
    World(int seed);
    void SetSeed(int seed);
    std::vector<Entity*>& GetEntities();
    void SummonEntity(Entity &entity);
    Block GetBlock(sf::Vector2i position);
    void PlaceBlock(sf::Vector2i position, Block &block);
    bool IsChunkExist(sf::Vector2i position);
    Chunk* GetChunk(sf::Vector2i position);
    void PlaceChunk(sf::Vector2i position);
    void LoadChunks(std::string file_path);
    void SaveChunks(std::string file_path);
    void GenerateChunk(sf::Vector2i position);
    void GenerateChunkHeightMap(sf::Vector2i position);
    void GenerateChunkBiomeMap(sf::Vector2i position);
    void GenerateChunkFeatures(sf::Vector2i position);
private:
    friend class RenderWorld;
    std::map<std::pair<int, int>, Chunk> m_chunks;
    std::vector<Entity*> m_entities;
    PerlinNoise m_noise_generator;
    int m_seed;
    std::mt19937 m_rng;
};

#endif /* SEQUOIA_ENGINE_SRC_WORLD_WORLD_ */
