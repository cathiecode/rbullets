class s01 : public Base::QueSheet {
private:
    double bulletRad;
    using Base::QueSheet::QueSheet;
    bool update() {
        if (lifeFrame == 600) {
            return false;
        }
        if ((lifeFrame % 60) == 0) {
            auto p = new Straight(bossX, bossY, texture["defaultbullet"]);
            BulletFire(p);
            p->speed = 1;
            p->rad = aimPlayer(bossX, bossY);
        }
        return true;
    }
};
