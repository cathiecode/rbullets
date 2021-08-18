class ZoomWhiteCircle : public Base::QueSheet {
    using Base::QueSheet::QueSheet;
public:
    double x, y;
    bool update() {
        if (lifeFrame == 255) {
            return false;
        }
        SDL_Rect rect;
        rect.x = playerX - ((lifeFrame * 64) / 2);
        rect.y = playerY - ((lifeFrame * 64) / 2);
        rect.w = lifeFrame * 64;
        rect.h = lifeFrame * 64;
        SDL_RenderCopy(renderer, texture["whitecircle"], NULL, &rect);
        return true;
    }
};

class ZoomBlackCircle : public Base::QueSheet {
    using Base::QueSheet::QueSheet;
public:
    double x, y;
    bool update() {
        if (lifeFrame == 255) {
            return false;
        }
        SDL_Rect rect;
        rect.x = 270 - ((lifeFrame * 64) / 2);
        rect.y = 540 - ((lifeFrame * 64) / 2);
        rect.w = lifeFrame * 64;
        rect.h = lifeFrame * 64;
        SDL_RenderCopy(renderer, texture["blackcircle"], NULL, &rect);
        return true;
    }
};

class BossKill : public Base::QueSheet {
    using Base::QueSheet::QueSheet;
public:
    double x, y;
    bool update() {
        if (lifeFrame == 61) {
            return false; // リザルト表示
        }
        if (lifeFrame % 30 == 0) {
            EffectFire(new ZoomBlackCircle());
        } else if (lifeFrame % 30 == 15) {
            EffectFire(new ZoomWhiteCircle());
        }
        bossX = 3000;
        bossY = 3000;
        return true;
    }
};
