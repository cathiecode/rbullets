class StraightAndAim : public Base::Bullet {
    using Base::Bullet::Bullet;
public:
    double rad = 0;
    double sSpeed = 1;
    double aSpeed = 3;
    double straightFrame = 90;
    bool update() {
        double speed;
        if (lifeFrame <= straightFrame) {
            speed = sSpeed;
        } else {
            speed = aSpeed;
        }
        if (lifeFrame == straightFrame) {
            rad = aimPlayer(x, y);
        }
        x = x + cos(rad) * speed;
        y = y + sin(rad) * speed;
        if ((x <= 0) || (540 <= x) || (y <= 0) || (720 <= y)) {
            return false;
        }
        return true;
    }
};

class r03 : public Base::QueSheet {
private:
    using Base::QueSheet::QueSheet;
    bool update() {
        if (lifeFrame == 600) {
            return false;
        }
        if ((lifeFrame % 120) == 0) {
            for (double deg = 0; deg < 360; deg += 360.0 / 16) {
                auto b = new StraightAndAim(bossX, bossY, texture["smallbullet"]);
                BulletFire(b);
                b->rad = deg2rad(deg);
                b->sSpeed = 0.75;
                b->aSpeed = 2;
                SEFire("bulletentry");
            }
        }
        if ((lifeFrame % 120) == 90) {
            SEFire("defaultbullet");
        }
        return true;
    }
};
