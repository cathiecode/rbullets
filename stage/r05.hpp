class r05 : public Base::QueSheet {
private:
    using Base::QueSheet::QueSheet;
    bool update() {
        if (lifeFrame == 60*15) {
            return false;
        }
        if ((lifeFrame % 90) == 0) {
            for (double deg = 0; deg < 360; deg += 90) {
                    auto b = new RotateZoom(bossX, bossY, texture["defaultbullet"]);
                    BulletFire(b);
                    b->radSpeed = deg2rad(1);
                    b->rad = deg2rad(deg);

                SEFire("defaultbullet");
            }
        }
        return true;
    }
};
