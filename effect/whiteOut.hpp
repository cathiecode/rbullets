class WhiteOut : public Base::QueSheet {
    using Base::QueSheet::QueSheet;
public:
    double x, y;
    bool update() {
        if (lifeFrame == 61) {
            return false;
        }
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 720 - lifeFrame * 48;
        rect.w = 540;
        rect.h = 1440;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderFillRect(renderer, &rect);
        return true;
    }
};
