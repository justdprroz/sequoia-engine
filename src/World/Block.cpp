#include <World/Block.hpp>
Block::Block() : mId(0), mBiome(0)
{
}

Block::Block(int id) : mId(id), mBiome(0)
{
}

Block::Block(int id, int biome) : mId(id), mBiome(biome)
{
}

int Block::GetId()
{
    return mId;
}

int Block::GetBiome()
{
    return mBiome;
}