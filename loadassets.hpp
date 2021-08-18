namespace Config {
    void setTexture(std::string id, std::string filename) {
        SDL_Surface* s;
        SDL_Texture* t;
        if ((s = SDL_LoadBMP(filename.c_str())) == NULL) {
            std::cerr << "テクスチャファイルの読み込みに失敗: " << SDL_GetError() << std::endl;
            exit(1);
        }
        if ((t = SDL_CreateTextureFromSurface(renderer, s)) == NULL) {
            std::cerr << "テクスチャファイルの生成に失敗: " << SDL_GetError() << std::endl;
            exit(1);
        }
        texture.insert(std::make_pair(id, t));
    }

    void setAudio(std::string id, std::string filename) {
        Mix_Chunk *a;
        if ((a = Mix_LoadWAV(filename.c_str())) == NULL) {
            std::cerr << "オーディオファイルの読み込みに失敗: " << Mix_GetError() << std::endl;
            exit(1);
        }
        audio.insert(std::make_pair(id, a));
    }
}

void loadassets() {
    using namespace Config;
    #include "assets.hpp"
}
