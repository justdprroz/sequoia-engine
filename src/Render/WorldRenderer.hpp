#ifndef SEQUOIA_ENGINE_SRC_RENDER_WORLD_RENDERER_
#define SEQUOIA_ENGINE_SRC_RENDER_WORLD_RENDERER_

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "World/World.hpp"
#include "Render/TextureManager.hpp"


// * Improved World Renderer Prototype
class WorldRenderer : public sf::Drawable, public sf::Transformable {
public:
    void Update(World& world, TextureManager& texture_manager);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::VertexArray tile_floor_vertices_;
    sf::VertexArray tile_wall_vertices_;
    sf::VertexArray tile_vertices_;
    sf::VertexArray entity_vertices_;
    sf::Texture* tile_atlas_;
    sf::Texture* entity_atlas_;
};

#endif /* SEQUOIA_ENGINE_SRC_RENDER_WORLD_RENDERER_ */
