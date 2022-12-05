#include <World/Chunk.hpp>
#include <fstream>
#include <iostream>
#include "Chunk.hpp"

Chunk::Chunk(){

};

Chunk::Chunk(sf::Vector2i origin) : origin_(origin)
{
}

Block Chunk::GetBlock(sf::Vector2i position)
{
    return blocks_[position.y][position.x];
}

std::array<std::array<Block, kChunkSize>, kChunkSize> &Chunk::GetBlocks()
{
    return blocks_;
}
void Chunk::PlaceBlock(sf::Vector2i position, const Block &block)
{
    blocks_[position.y][position.x] = block;
}

sf::Vector2i Chunk::GetOrigin()
{
    return origin_;
}

void Chunk::SetGenerated()
{
    is_generated_ = true;
}

void Chunk::SetGenerated(bool state)
{
    is_generated_ = state;
}

bool Chunk::IsGenerated()
{
    return is_generated_;
}

// FIXME: normal serialization
void Chunk::SaveChunk(std::string file_path)
{
    std::ofstream chunkfile;
    chunkfile.open(file_path);
    if (!chunkfile.is_open())
    {
        std::cout << "Failed open " << file_path << '\n';
        return;
    }
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            int l_id = blocks_[i][j].GetId();
            chunkfile.write(reinterpret_cast<char *>(&l_id), sizeof(l_id));
        }
    }
    chunkfile.close();
}

// FIXME: normal deserialization
void Chunk::LoadChunk(std::string file_path)
{
    std::ifstream chunkfile;
    chunkfile.open(file_path);
    if (!chunkfile.is_open())
    {
        std::cout << "Failed open " << file_path << '\n';
        return;
    }
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            int l_id;
            chunkfile.read(reinterpret_cast<char *>(&l_id), sizeof(l_id));
            blocks_[i][j] = {l_id};
        }
    }
    chunkfile.close();
}