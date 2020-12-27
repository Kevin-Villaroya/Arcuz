#ifndef __TEXTURE_TOOL_H__
#define __TEXTURE_TOOL_H__

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Network/Packet.hpp>
#include <string>

class TextureTool : public sf::Texture{
private:
  void resizeTextureLessAlpha(std::string locationAsset);
  void findNotAlphaPixelsIn(const sf::Image &image, int &xMin, int &xMax, int &yMin, int &yMax);

public:
  TextureTool();
  TextureTool(std::string locationAsset);
};

sf::Packet& operator <<(sf::Packet& packet, TextureTool& texture);
sf::Packet& operator >>(sf::Packet& packet, TextureTool& texture);

#endif
