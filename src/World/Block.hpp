#ifndef SOURCE_WORLD_BLOCK_HPP
#define SOURCE_WORLD_BLOCK_HPP

class Block
{
public:
    Block();
    Block(int);
    Block(int, int);
    int GetId();
    int GetBiome();

private:
    int mId;
    int mBiome;
};

#endif // SOURCE_WORLD_BLOCK_HPP