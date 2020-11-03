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

  const std::vector<TextureTool*>& getDeadTextures();
  const std::vector<TextureTool*>& getIdleTextures();
  const std::vector<TextureTool*>& getJumpTextures();
  const std::vector<TextureTool*>& getRunTextures();
  const std::vector<TextureTool*>& getWalkTextures();
};

#endif
