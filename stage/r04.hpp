class RotateZoom : public Base::Bullet {
    using Base::Bullet::Bullet;
public:
    double rad = 0;
    double speed = 1;
    double originX, originY;
    double radSpeed = deg2rad(1);
    bool update() {
        if (lifeFrame == 0) {
            originX = x;
            originY = y;

        }
        rad = rad + radSpeed;
        x = cos(rad) * (speed * lifeFrame) + originX;
        y = sin(rad) * (speed * lifeFrame) + originY;
        return true;
    }
};

class r04 : public Base::QueSheet {
private:
    using Base::QueSheet::QueSheet;
    bool update() {
        if (lifeFrame == 60*30) {
            return false;
        }
        if ((lifeFrame % 15) == 0) {
            for (double deg = 0; deg < 360; deg += 360.0 / 4) {
                auto b = new RotateZoom(bossX, bossY, texture["smallbullet"]);
                BulletFire(b);
                b->rad = deg2rad(deg + (lifeFrame));
                b->radSpeed = deg2rad(0.5);
                SEFire("defaultbullet");
            }
        }
        return true;
    }
};
