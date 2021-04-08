#include "StructureTexture.h"
#include <experimental/filesystem>
#include <iostream>

StructureTexture StructureTexture::instance;

StructureTexture::StructureTexture(){
  std::string path = "assets/structures";
  std::string pathchild;

  for (const auto & file : std::experimental::filesystem::directory_iterator(path)){
    pathchild = file.path();
    std::vector<TextureTool*> textures;

    this->nameTextures.push_back(file.path().filename().string());
    this->structureTextures.push_back(textures);

    for (const auto & file : std::experimental::filesystem::directory_iterator(pathchild)){
      this->structureTextures[this->structureTextures.size() - 1].push_back(new TextureTool(file.path()));
    }
  }
}

const std::vector<TextureTool*>& StructureTexture::getTexturesOf(const std::string& nameStructure){
  for(unsigned int i = 0; i < StructureTexture::instance.nameTextures.size(); i++){
    if(StructureTexture::instance.nameTextures[i].compare(nameStructure) == 0){
      return StructureTexture::instance.structureTextures[i];
    }
  }
  return StructureTexture::instance.structureTextures[0];
}

StructureTexture::~StructureTexture(){
  for(unsigned int i = 0; i < this->structureTextures.size(); i++){
    for(unsigned int j = 0; j < this->structureTextures[i].size(); j++){
      delete this->structureTextures[i][j];
    }
  }
}