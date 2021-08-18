class WaterDrop : public Base::QueSheet {
    using Base::QueSheet::QueSheet;
public:
    double x, y;
    bool update() {
        if (lifeFrame == 255) {
            return false;
        }
        SDL_Rect rect;
        rect.x = playerX - (lifeFrame / 2);
        rect.y = playerY - (lifeFrame / 2);
        rect.w = lifeFrame;
        rect.h = lifeFrame;
        SDL_SetTextureAlphaMod(texture["waterdrop"], 255 - lifeFrame);
        SDL_RenderCopy(renderer, texture["waterdrop"], NULL, &rect);
        return true;
    }
};
