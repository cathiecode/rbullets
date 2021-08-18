class Straight : public Base::Bullet {
    using Base::Bullet::Bullet;
public:
    double rad = 0;
    double speed = 1;
    bool update() {
        x = x + cos(rad) * speed;
        y = y + sin(rad) * speed;
        if ((x <= 0) || (540 <= x) || (y <= 0) || (720 <= y)) {
            return false;
        }
        return true;
    }
};

class r01 : public Base::QueSheet {
private:
    int bulletCount;
    using Base::QueSheet::QueSheet;
    bool update() {
        if (lifeFrame == 600) {
            return false;
        }
        if ((lifeFrame % 2) == 0) {
            auto p = new Straight(bossX, bossY, texture["defaultbullet"]);
            BulletFire(p);
            SEFire("defaultbullet");
            p->speed = 2;
            p->rad = deg2rad(137.5 * bulletCount);
            bulletCount++;
        }
        return true;
    }
};
