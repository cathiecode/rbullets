bool playScene();
bool gameLoop();
void windowClear();
void processEvent();
void buttonStateCheck();
void updateAllObjects();
void checkCollision();
void rendering();
void textPrint();
void stateRendering();
void keepFPS();
void debugPrint();
void keyboardCheck(SDL_Event);
void miss();
void playerBulletFire();
void other();
void gameover();
void bosskill();
void clearLoop();
void result();

void windowClear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 64, 255);
    SDL_RenderClear(renderer);
}

void processEvent() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                exit(0);
                break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:
                keyboardCheck(event);
                break;
            default:
                break;
        }
    }
}

void keepFPS() {
    SDL_Delay(16);
}

void playerBulletFire(){
    if ((frame % 5) == 0) {
        auto b = new Straight(playerX, playerY, texture["playerbullet"]);
        PlayerBulletFire(b);
        b->rad = deg2rad(270);
        b->speed = 10;
        SEFire("playerbullet");
    }
}

void updateAllObjects() {
    std::shared_ptr<Base::Bullet> bullet_ptr;
    auto bullet_itr = bulletList.begin();
    while(bullet_itr != bulletList.end()) {
        bullet_ptr = *bullet_itr;
        if (!bullet_ptr->update()) {
            bullet_itr = bulletList.erase(bullet_itr);
            continue;
        } else {
            bullet_ptr->_update();
        }
        bullet_itr++;
    }

    bullet_itr = playerBulletList.begin();
    while(bullet_itr != playerBulletList.end()) {
        bullet_ptr = *bullet_itr;
        if (!bullet_ptr->update()) {
            bullet_itr = playerBulletList.erase(bullet_itr);
            continue;
        } else {
            bullet_ptr->_update();
        }
        bullet_itr++;
    }

    auto queSheet_itr = effectList.begin();
    while(queSheet_itr != effectList.end()) {
        auto queSheet_ptr = *queSheet_itr;
        if (!queSheet_ptr->update()) {
            queSheet_itr = effectList.erase(queSheet_itr);
            continue;
        } else {
            queSheet_ptr->_update();
        }
        queSheet_itr++;
    }
}

void textPrint(std::string s, int x, int y, int r = 0xaa, int g = 0x00, int b = 0x22) {
    SDL_Color color = {r, g, b};
    SDL_Surface *textSurface = TTF_RenderUTF8_Blended(font, s.c_str(), color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    SDL_QueryTexture(textTexture, NULL, NULL, &dstRect.w, &dstRect.h);
    SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);
    SDL_DestroyTexture(textTexture);
}

void stateRendering() {
    textPrint("得点:     " + std::to_string(displayscore), 10, 720 + 10);
    textPrint("残り時間: " + std::to_string((60 * 60 * 3 - frame)/60) + "秒", 10, 720 + 10 + 32);
    textPrint("残機:     " + std::to_string(playerRemain), 10, 720 + 10 + 32 * 2);
    textPrint("ボスHP:   " + std::to_string(displayBossHP), 10, 720 + 10 + 32 * 3);
}

void other() {
    if (score >= displayscore) {
        displayscore += (score - displayscore) / 30;
    }
    if (bossHP <= displayBossHP) {
        displayBossHP += (bossHP - displayBossHP) / 30;
    }

    if ((frame % 120) == 0) {
        auto b = new WaterDrop();
        EffectFire(b);
        b->x = playerX;
        b->y = playerY;
     }

     if (bossHP <= 0) {
         bosskill();
     }
}

void rendering() {
    SDL_ClearError();
    std::shared_ptr<Base::Bullet> bullet_ptr;
    SDL_Rect rect;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    auto bullet_itr = bulletList.begin();
    while (bullet_itr != bulletList.end()) {
        bullet_ptr = *bullet_itr;
        if (SDL_QueryTexture(bullet_ptr->texture, NULL, NULL, &rect.w, &rect.h)) {
            std::cout << "SDL_QueryTextureに失敗しました。" << std::endl;
            bullet_itr++;
            continue;
        }
        rect.x = bullet_ptr->x - (rect.w / 2);
        rect.y = bullet_ptr->y - (rect.h / 2);
        SDL_RenderCopy(renderer, bullet_ptr->texture, NULL, &rect);
        bullet_itr++;
    }

    bullet_itr = playerBulletList.begin();
    while (bullet_itr != playerBulletList.end()) {
        bullet_ptr = *bullet_itr;
        if (SDL_QueryTexture(bullet_ptr->texture, NULL, NULL, &rect.w, &rect.h)) {
            std::cout << "SDL_QueryTextureに失敗しました。" << std::endl;
            bullet_itr++;
            continue;
        }
        rect.x = bullet_ptr->x - (rect.w / 2);
        rect.y = bullet_ptr->y - (rect.h / 2);
        SDL_RenderCopy(renderer, bullet_ptr->texture, NULL, &rect);
        bullet_itr++;
    }

    if (SDL_QueryTexture(texture["player"], NULL, NULL, &rect.w, &rect.h)) {
        std::cout << "SDL_QueryTextureに失敗しました。" << std::endl;
    }
    rect.x = playerX - (rect.w / 2);
    rect.y = playerY - (rect.h / 2);
    SDL_RenderCopy(renderer, texture["player"], NULL, &rect);

    if (SDL_QueryTexture(texture["boss"], NULL, NULL, &rect.w, &rect.h)) {
        std::cout << "SDL_QueryTextureに失敗しました。" << std::endl;
    }
    rect.x = bossX - (rect.w / 2);
    rect.y = bossY - (rect.h / 2);
    SDL_RenderCopy(renderer, texture["boss"], NULL, &rect);

    rect.x = 0;rect.y = 720;
    rect.w = 540;rect.h=240;
    SDL_RenderCopy(renderer, texture["fg"], NULL, &rect);
    stateRendering();
    //std::cout << SDL_GetError() << std::endl;
    SDL_RenderPresent(renderer);
}

void debugPrint() {
    for (int i = 0; i < 1024; i++) {
        std::cout << Mix_Playing(i);
    }
    std::cout << std::endl;
}

void miss() {
    bulletList.clear();
    playerX = 270;
    playerY = 500;
    playerRemain--;
    EffectFire(new WhiteOut());
    SEFire("miss");
    if (playerRemain == -1) {
        gameover();
    }
}

void bosskill() {
    if (isBSed) {
        return;
    }
    bulletList.clear();
    playerBulletList.clear();
    sceneList.clear();
    EffectFire(new BossKill());
    SEFire("bosskill");
    displayBossHP = 0;
    std::cout << "ボスが倒されました。" << std::endl;
    isBSed = true;
    for (int i = 0; i <= 60 * 4; i++) {
        clearLoop();
    }
    result();
}

void gameover() {
    exit (2);
}

void checkCollision() {
    auto bullet_itr = bulletList.begin();
    std::shared_ptr<Base::Bullet> bullet_ptr;
    int bulletW, bulletH;
    double bulletSize;
    while (bullet_itr != bulletList.end()) {
        bullet_ptr = *bullet_itr;
        if (SDL_QueryTexture(bullet_ptr->texture, NULL, NULL, &bulletW, &bulletH)) {
            std::cout << "SDL_QueryTextureに失敗しました。" << std::endl;
            bullet_itr++;
            continue;
        }
        bulletSize = 0.75 * ((bulletW + bulletH) / 2);

        if (sqrt(pow(bullet_ptr->x - playerX, 2) + pow(bullet_ptr->y - playerY, 2)) <= (bulletSize / 2 + 4)) {
            std::cout << "あたっとるで" << std::endl;
            miss();
            break;
        }

        bullet_itr++;
    }

    bullet_itr = playerBulletList.begin();
    while (bullet_itr != playerBulletList.end()) {
        bullet_ptr = *bullet_itr;
        if (SDL_QueryTexture(bullet_ptr->texture, NULL, NULL, &bulletW, &bulletH)) {
            std::cout << "SDL_QueryTextureに失敗しました。" << std::endl;
            bullet_itr++;
            continue;
        }
        bulletSize = 0.75 * ((bulletW + bulletH) / 2);

        if (sqrt(pow(bullet_ptr->x - bossX, 2) + pow(bullet_ptr->y - bossY, 2)) <= (bulletSize / 2 + 64)) {
            //std::cout << "ボスに当たっています" << std::endl;
            score+=10;
            bossHP-=10;
            bullet_itr = playerBulletList.erase(bullet_itr);
            break;
        }
        bullet_itr++;
    }
}

void keyboardCheck(SDL_Event event) {
    bool changeTo = false;
    if (event.key.type == SDL_KEYDOWN) {
        changeTo = true;
    }

    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_UP:
            Button::up = changeTo;
        break;
        case SDL_SCANCODE_DOWN:
            Button::down = changeTo;
        break;
        case SDL_SCANCODE_LEFT:
            Button::left = changeTo;
        break;
        case SDL_SCANCODE_RIGHT:
            Button::right = changeTo;
        break;
        case SDL_SCANCODE_LSHIFT:
            Button::slow = changeTo;
        break;
        case SDL_SCANCODE_X:
            Button::bomb = changeTo;
        break;
    }
}

void buttonStateCheck() { // キーボード操作用のアレ
    double acc = 10;
    if (Button::slow) {
        acc = 4;
    }
    if (Button::down && (720 - 20 >= playerY)) {
        playerY += acc;
    }
    if (Button::up && (0 + 20 <= playerY)) {
        playerY -= acc;
    }
    if (Button::left && (0 + 20 <= playerX)) {
        playerX -= acc;
    }
    if (Button::right && (540 - 20 >= playerX)) {
        playerX += acc;
    }
    if (Button::bomb) {

    }
}

bool gameLoop() {
    windowClear();
    processEvent();
    playerBulletFire();
    //serial2button();
    buttonStateCheck();
    updateAllObjects();
    checkCollision();
    other();
    rendering();
    frame++;
    keepFPS();
    return true;
}

void clearLoop() {
    windowClear();
    processEvent();
    //serial2button();
    buttonStateCheck();
    updateAllObjects();
    other();
    rendering();
    frame++;
    keepFPS();
}

void playScene(std::shared_ptr<Base::QueSheet> queSheet) {
    while (queSheet->update()) {
        gameLoop();
        queSheet->_update();
    }
}

void game() { //ゲーム全体を総括するルーチン
    title();
    for (std::shared_ptr<Base::QueSheet> queSheet : sceneList) { // シーンの再生
        std::cout << "シーン再生開始" << std::endl;
        playScene(queSheet);
    }
}

void title() {
    SDL_Rect rect;
    while (1) {
        windowClear();
        processEvent();
        rect.x = 0;
        rect.y = 0;
        rect.w = 540;
        rect.h = 960;
        SDL_RenderCopy(renderer, texture["title"], NULL, &rect);

        //serial2button();
        if (Button::slow) {
            break;
        }
        SDL_RenderPresent(renderer);
        keepFPS();
    }
}

void result() {
    SDL_Rect rect;
    int frame=0;
    int totalscore = score + playerRemain * 5000;
    std::string resultText;
    while (1) {
        windowClear();
        processEvent();
        rect.x = 0;
        rect.y = 0;
        rect.w = 540;
        rect.h = 960;
        SDL_RenderCopy(renderer, texture["result"], NULL, &rect);

        // リザルト表示コード
        textPrint("スコア:     " + std::to_string(score) + "点", 20, 300, 0xff, 0xff, 0xff);
        textPrint("Press A to back to the title.", 20, 332, 0xff, 0xaa, 0xaa);

        //serial2button();
        if (Button::slow) {
            break;
        }
        SDL_RenderPresent(renderer);
        keepFPS();
    }
    exit (1);
}
