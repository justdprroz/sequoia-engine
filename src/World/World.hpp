// Copyright 2021-2022 JustDprroz

#ifndef SOURCE_WORLD_WORLD_HPP_
#define SOURCE_WORLD_WORLD_HPP_

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

#include <World/Chunk.hpp>
#include <World/Block.hpp>
#include <World/Entity.hpp>

const int kChunkSize = 16;

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
    void NoiseInit();
private:
    std::map<std::pair<int, int>, Chunk> chunks_;
    std::vector<Entity*> entities_;
    FastNoiseLite noise_block_;
    FastNoiseLite noise_biome_;
    int seed_;
    friend class RenderWorld;
};

#endif  // SOURCE_WORLD_WORLD_HPP_
