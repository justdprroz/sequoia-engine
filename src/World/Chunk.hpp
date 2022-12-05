#ifndef SOURCE_WORLD_CHUNK_HPP_
#define SOURCE_WORLD_CHUNK_HPP_

#include <string>
#include <array>
#include <SFML/System/Vector2.hpp>
#include <World/Block.hpp>

const int kChunkSize = 32;

class Chunk
{
public:
    Chunk();
    Chunk(sf::Vector2i origin);
    Block GetBlock(sf::Vector2i position);
    std::array<std::array<Block, kChunkSize>, kChunkSize>& GetBlocks();
    void PlaceBlock(sf::Vector2i position, const Block &block);
    sf::Vector2i GetOrigin();
    void SaveChunk(std::string file_path);
    void LoadChunk(std::string file_path);
    void SetGenerated();
    void SetGenerated(bool state);
    bool IsGenerated();

private:
    sf::Vector2i origin_;
    bool is_generated_;
    std::array<std::array<Block, kChunkSize>, kChunkSize> blocks_;
    friend class RenderChunk;
    friend class Renderer;
};

#endif // SOURCE_WORLD_CHUNK_HPP_