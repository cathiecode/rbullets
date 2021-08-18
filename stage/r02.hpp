class r02 : public Base::QueSheet {
private:
    double bulletRad;
    using Base::QueSheet::QueSheet;
    bool update() {
        if (lifeFrame == 60*15) {
            return false;
        }
        if ((lifeFrame % 2) == 0) {
            auto p = new Straight(bossX, bossY, texture["defaultbullet"]);
            BulletFire(p);
            p->speed = 1;
            p->rad = bulletRad;
            bulletRad = bulletRad + deg2rad((360.0 / 30));
            SEFire("smallbullet");
        }
        if ((lifeFrame % 120) == 119) {
            auto p = new Straight(bossX, bossY, texture["specialbullet"]);
            BulletFire(p);
            p->speed = 1;
            p->rad = aimPlayer(bossX, bossY);
            SEFire("defaultbullet");
        }
        return true;
    }
};
