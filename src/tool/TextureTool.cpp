#include "TextureTool.h"
#include <algorithm>
#include <iostream>

TextureTool::TextureTool() : sf::Texture() {}

TextureTool::TextureTool(std::string locationFolder) : sf::Texture(){
  this->loadFromFile(locationFolder);
  this->resizeTextureLessAlpha(locationFolder);
}

void TextureTool::resizeTextureLessAlpha(std::string locationAsset){
  sf::Image oldImage = this->copyToImage();
  sf::Image newImage;

  int width = oldImage.getSize().x; int height = oldImage.getSize().y;
  int xMin = width; int xMax = 0; int yMin = height; int yMax = 0;

  this->findNotAlphaPixelsIn(oldImage, xMin, xMax, yMin, yMax);

  newImage.create(xMax - xMin, yMax - yMin);

  for(int i = xMin; i < xMax; i++){
    for(int j = yMin; j < yMax; j++){
      newImage.setPixel(i - xMin, j - yMin, oldImage.getPixel(i,j));
    }
  }

  this->loadFromImage(newImage);
}


void TextureTool::findNotAlphaPixelsIn(const sf::Image &oldImage, int &xMin, int &xMax, int &yMin, int &yMax){
  int width = oldImage.getSize().x;
  int height = oldImage.getSize().y;

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      if(oldImage.getPixel(i, j).a != 0){ //if pixel is not transparent
        xMin = std::min(xMin, i);
        xMax = std::max(xMax, i);
        yMin = std::min(yMin, j);
        yMax = std::max(yMax, j);
      }
    }
  }
}
