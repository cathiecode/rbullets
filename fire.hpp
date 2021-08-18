double deg2rad(double deg) {
    return M_PI * 2 * (deg / 360);
}

double aimPlayer(double x, double y) {
    return atan2(playerY - y, playerX - x);
}

void BulletFire(Base::Bullet* bullet) {
    bulletList.push_back(std::shared_ptr<Base::Bullet>(bullet));
}

void PlayerBulletFire(Base::Bullet* bullet) {
    playerBulletList.push_back(std::shared_ptr<Base::Bullet>(bullet));
}

void EffectFire(Base::QueSheet* effect) {
    effectList.push_back(std::shared_ptr<Base::QueSheet>(effect));
}

void SEFire(std::string id) {
    if (Mix_PlayChannel(-1, audio[id], 0) == -1) {
        std::cerr << "再生失敗" << std::endl;
        return;
    }
}
