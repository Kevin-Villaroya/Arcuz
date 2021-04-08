#ifndef  __STRUCTURE_TEXTURE_H__
#define __STRUCTURE_TEXTURE_H__

#include <string>
#include <vector>
#include "../../tool/TextureTool.h"

class StructureTexture{
  private:
    std::vector<std::string> nameTextures;//can be a animation or a single texture
    std::vector<std::vector<TextureTool*>> structureTextures;//there is all textures for all structures

    static StructureTexture instance;
    StructureTexture();

  public:
    static const std::vector<TextureTool*>& getTexturesOf(const std::string& nameStructure);

    ~StructureTexture();
};

#endif