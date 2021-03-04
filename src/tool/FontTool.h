#ifndef __FONT_TOOL_H__
#define __FONT_TOOL_H__

#include <SFML/Graphics.hpp>

class FontTool : public sf::Font{
    public:
        static const FontTool REGULAR_FONT;

        FontTool();
        FontTool(const std::string& locationFolder);
};



#endif