#include "TextureTool.h"
#include <algorithm>

TextureTool::TextureTool() : sf::Texture() {}

TextureTool::TextureTool(std::string locationFolder) : sf::Texture(){
  this->loadFromFile(locationFolder);
  this->resizeTextureLessAlpha();
}

void TextureTool::resizeTextureLessAlpha(){
  sf::Image oldImage = this->copyToImage();
  sf::Image newImage;
  int width = oldImage.getSize().x;
  int height = oldImage.getSize().y;

  int xMin = width;
  int xMax = 0;
  int yMin = height;
  int yMax = 0;

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      if(oldImage.getPixel(i, j).a != 0){ //if pixel is not transparent
        xMin = std::min(xMin,i);
        xMax = std::max(xMax,i);
        yMin = std::min(yMin,j);
        yMax = std::max(yMax,j);
      }
    }
  }

  newImage.create(xMax - xMin, yMax - yMin);

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      if(!(i < xMin || i >= xMax || j < yMin || j >= yMax)){
        newImage.setPixel(i - xMin, j - yMin, oldImage.getPixel(i,j));
      }
    }
  }
  this->loadFromImage(newImage);

}
