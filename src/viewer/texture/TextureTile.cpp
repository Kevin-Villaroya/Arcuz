#include "TextureTile.h"

TextureTool TextureTile::GRASS_TEXTURE(TextureTool("assets/tiles/grass.png"));
TextureTool TextureTile::GROUND_TEXTURE(TextureTool("assets/tiles/ground.png"));
TextureTool TextureTile::EMPTY_TEXTURE(TextureTool("assets/tiles/empty.png"));
TextureTool TextureTile::FOREST_TEXTURE(TextureTool("assets/tiles/forest.png"));
TextureTool TextureTile::MOUNTAIN_TEXTURE(TextureTool("assets/tiles/mountain.png"));

TextureTool* TextureTile::getGrassTexture(){
	return &TextureTile::GRASS_TEXTURE;
}

TextureTool* TextureTile::getGroundTexture(){
	return &TextureTile::GROUND_TEXTURE;
}

TextureTool* TextureTile::getForestTexture(){
	return &TextureTile::FOREST_TEXTURE;
}

TextureTool* TextureTile::getMountainTexture(){
	return &TextureTile::MOUNTAIN_TEXTURE;
}

TextureTool* TextureTile::getEmptyTexture(){
	return &TextureTile::EMPTY_TEXTURE;
}