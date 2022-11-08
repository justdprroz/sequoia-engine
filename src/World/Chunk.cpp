#include <World/Chunk.hpp>
#include <fstream>
#include <iostream>

Chunk::Chunk(){

};

Chunk::Chunk(sf::Vector2i origin) : mOrigin(origin)
{
}

Block Chunk::GetBlock(sf::Vector2i position)
{
    return mBlocks[position.x][position.y];
}

void Chunk::PlaceBlock(sf::Vector2i position, const Block &block)
{
    mBlocks[position.x][position.y] = block;
}

sf::Vector2i Chunk::GetOrigin()
{
    return mOrigin;
}

void Chunk::SetGenerated()
{
    mIsGenerated = true;
}

void Chunk::SetGenerated(bool state)
{
    mIsGenerated = state;
}

bool Chunk::IsGenerated()
{
    return mIsGenerated;
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
            int l_id = mBlocks[i][j].GetId();
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
            mBlocks[i][j] = {l_id};
        }
    }
    chunkfile.close();
}