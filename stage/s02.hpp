class FetherFall : public Base::Bullet {
    using Base::Bullet::Bullet;
public:
    double speed = 1;
    double width = 50;
    int cycle = 60;
    double originX;
    bool update() {
        if (lifeFrame == 0) {
            originX = x;
        }
        y = y + speed;
        x = sin(deg2rad(((double)(lifeFrame % cycle) / cycle)) * 360)*width + originX;
        if (720 <= y) {
            return false;
        }
        return true;
    }
};

class s02 : public Base::QueSheet {
private:
    double bulletRad;
    using Base::QueSheet::QueSheet;
    bool update() {
        if (lifeFrame == 60*15) {
            return false;
        }
        if ((lifeFrame % 5) == 0) {
            for (int j = 0; j < 2; j++) {
                for (int i = 0; i < 3; i++) {
                    auto b = new Straight(bossX, bossY, texture["smallbullet"]);
                    BulletFire(b);
                    b->speed = 5;
                    b->rad = deg2rad((i - 1) * 15 + j * 180);
                }
            }
            SEFire("defaultbullet");
        }
        if (lifeFrame >= 120 && (lifeFrame % 120) == 0) {
            for (int i = 0; i <= 540; i += 54) {
                auto b = new FetherFall(i, 0, texture["smallbullet"]);
                BulletFire(b);
                b->cycle = 240;
                b->width = 54;
            }
        }
        return true;
    }
};
