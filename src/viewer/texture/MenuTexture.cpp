#include "MenuTexture.h"

TextureTool MenuTexture::CADRE_MINIMAP(TextureTool("assets/hud/minimap/cadre.png"));
TextureTool MenuTexture::MENU_SOLO(TextureTool("assets/icone/solo.png"));
TextureTool MenuTexture::MENU_JOIN(TextureTool("assets/icone/join.png"));
TextureTool MenuTexture::MENU_HOST(TextureTool("assets/icone/host.png"));
TextureTool MenuTexture::MENU_ARMOIRE(TextureTool("assets/icone/armoire.png"));
TextureTool MenuTexture::MENU_FOND(TextureTool("assets/menu/fond.png"));

TextureTool* MenuTexture::getMenuFond(){
	return &MenuTexture::MENU_FOND;
}

TextureTool* MenuTexture::getMenuArmoire(){
	return &MenuTexture::MENU_ARMOIRE;
}

TextureTool* MenuTexture::getMenuHost(){
	return &MenuTexture::MENU_HOST;
}

TextureTool* MenuTexture::getMenuJoin(){
	return &MenuTexture::MENU_JOIN;
}

TextureTool* MenuTexture::getMenuSolo(){
	return &MenuTexture::MENU_SOLO;
}

TextureTool* MenuTexture::getCadreMinimap(){
	return &MenuTexture::CADRE_MINIMAP;
}