#include "Assets.h"

Assets::Assets() {
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_BILINEAR);

    painting = rl::Texture(Path("Painting.png"));
    window = rl::Texture(Path("Window.png"));
    wall = rl::Texture(Path("Wall.png"));
    clock = rl::Texture(Path("Clock.png"));
    hourHand = rl::Texture(Path("HourHand.png"));
    minHand = rl::Texture(Path("MinHand.png"));
    nextEventBtn = rl::Texture(Path("NextEventBtn.png"));
    tutorial = rl::Texture(Path("Tutorial.png"));
}

std::string Assets::Path(std::string name) {
    return basePath + name;
}

rl::Rectangle Assets::TexRect(rl::Texture& tex) {
    return rl::Rectangle(0, 0, tex.width, tex.height);
}

