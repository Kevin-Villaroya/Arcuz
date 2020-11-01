#ifndef __TEXTURE_h__
#define __TEXTURE_h__

#include <SFML/Graphics/Texture.hpp>
#include <string>

class TextureTool : public sf::Texture{
private:

public:
  TextureTool(std::string locationAsset);
};

#endif
