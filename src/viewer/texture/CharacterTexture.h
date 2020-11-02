#ifndef  __CHARACTER_TEXTURE_H__
#define __CHARACTER_TEXTURE_H__

#include "../../tool/TextureTool.h"

class CharacterTexture{
private:
  std::vector<TextureTool*> idle;
  std::vector<TextureTool*> walk;
  std::vector<TextureTool*> run;
  std::vector<TextureTool*> jump;
  std::vector<TextureTool*> dead;

  void setDeadTextures(std::string type);
  void setIdleTextures(std::string type);
  void setJumpTextures(std::string type);
  void setRunTextures(std::string type);
  void setWalkTextures(std::string type);

  CharacterTexture(std::string type);
public:
  static CharacterTexture* MAN_TEXTURES;
  static CharacterTexture* GIRL_TEXTURES;

  ~CharacterTexture();

  std::vector<TextureTool*>& getDeadTextures();
  std::vector<TextureTool*>& getIdleTextures();
  std::vector<TextureTool*>& getJumpTextures();
  std::vector<TextureTool*>& getRunTextures();
  std::vector<TextureTool*>& getWalkTextures();
};

#endif
