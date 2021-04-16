#ifndef __TEXTURE_TILE_H
#define __TEXTURE_TILE_H

#include "../../tool/TextureTool.h"
#include <memory>

class TextureTile{
private:
  static TextureTool GRASS_TEXTURE;
  static TextureTool GROUND_TEXTURE;
  static TextureTool FOREST_TEXTURE;
  static TextureTool MOUNTAIN_TEXTURE;
  static TextureTool EMPTY_TEXTURE;

public:
	static TextureTool* getGrassTexture();
	static TextureTool* getGroundTexture();
	static TextureTool* getForestTexture();
	static TextureTool* getMountainTexture();
	static TextureTool* getEmptyTexture();
};

#endif
