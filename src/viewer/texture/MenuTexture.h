#ifndef __MENU_TEXTURE_H
#define __MENU_TEXTURE_H

#include "../../tool/TextureTool.h"
#include <memory>

class MenuTexture{
private:
  static TextureTool CADRE_MINIMAP;
  static TextureTool MENU_SOLO;
  static TextureTool MENU_JOIN;
  static TextureTool MENU_HOST;
  static TextureTool MENU_ARMOIRE;
  static TextureTool MENU_FOND;

public:
	static TextureTool* getMenuFond();
	static TextureTool* getMenuArmoire();
	static TextureTool* getMenuHost();
	static TextureTool* getMenuJoin();
	static TextureTool* getMenuSolo();
	static TextureTool* getCadreMinimap();
	~MenuTexture();
};

#endif
