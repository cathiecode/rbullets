#include <cmath>
#include <string>
#include <map>
#include <list>
#include <iostream>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

// クラス定義
namespace Base {
    class QueSheet {
    protected:
        int lifeFrame = 0;
    public:
        QueSheet(){};
        virtual ~QueSheet(){};
        virtual bool update(){return true;};
        void _update(){lifeFrame++;};
    };

    class Object : public QueSheet {
    public:
        double x, y;
        SDL_Texture* texture;
        Object(double originX, double originY, SDL_Texture* t){
            x = originX;
            y = originY;
            texture = t;
        };
        virtual ~Object(){};
        virtual bool update(){return true;};
    };

    class Bullet : public Object {
        using Object::Object;
    public:
        double size;
        virtual ~Bullet(){};
        virtual bool update(){return true;};
    };
}
// グローバル変数
double playerX = 270;
double playerY = 500;
double bossX = 270;
double bossY = 260;
int score = 0;
int displayscore = 0;
int frame = 0;
int playerRemain = 5;
int bossHP = 5000;
int displayBossHP = bossHP;
bool isBSed = false;

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;

std::map<std::string, SDL_Texture*> texture;
std::map<std::string, Mix_Chunk*> audio;
std::map<std::string, int> audioReserveChannel;

std::list<std::shared_ptr<Base::QueSheet>> effectList;
std::list<std::shared_ptr<Base::QueSheet>> sceneList;
std::list<std::shared_ptr<Base::Object>> bgDotList;
std::list<std::shared_ptr<Base::Bullet>> bulletList;
std::list<std::shared_ptr<Base::Bullet>> playerBulletList;

namespace Button {
    bool left, right, up, down;
    bool bomb, slow;
}

void init();
void title();
void game();
void result();
void cleanup();

#include "serial.hpp"
#include "fire.hpp"
#include "loadassets.hpp"
#include "loadais.hpp"
#include "game.cpp"

void init() {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        std::cerr << "SDLの初期化に失敗: " << SDL_GetError() << std::endl;
        exit (1);
    }
    if (TTF_Init()) {
        std::cerr << "TTFの初期化に失敗: " << TTF_GetError() << std::endl;
        //exit(1);
    }
    if (Mix_Init(MIX_INIT_FLAC|MIX_INIT_MOD)) {
        std::cerr << "音声の初期化に失敗: " << TTF_GetError() << std::endl;
        //exit(1);
    }
    if (SDL_CreateWindowAndRenderer(540, 960, SDL_WINDOW_OPENGL, &window, &renderer)) {
        std::cerr << "ウィンドウの作成に失敗: " << SDL_GetError() << std::endl;
        exit(1);
    }
    if ((font = TTF_OpenFont("assets/mgen.ttf", 32)) == NULL) {
        std::cerr << "フォントの読み込みに失敗: " << TTF_GetError() << std::endl;
        exit(1);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512)) {
        std::cerr << "オーディオの開始に失敗: " << SDL_GetError() << std::endl;
        exit(1);
    }
    Mix_AllocateChannels(1024);
    loadassets();
    //serialinit();
    atexit(cleanup);
}

void cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
    std::cerr << "正常に終了" << std::endl;
}

int main() {
    init();
    loadais();
    //title();
    game();
    //result();
}
