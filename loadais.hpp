#include "stage/r01.hpp"
#include "stage/r02.hpp"
#include "stage/r03.hpp"
#include "stage/r04.hpp"
#include "stage/r05.hpp"
#include "stage/s01.hpp"
#include "stage/s02.hpp"

#include "effect/waterEffect.hpp"
#include "effect/whiteOut.hpp"
#include "effect/BossKill.hpp"

template <class S> void Scene(S scene) {
    sceneList.push_back(std::shared_ptr<Base::QueSheet>(scene));
}

void loadais() {
    Scene(new r05());
    Scene(new r03());
    Scene(new r01());
    Scene(new r02());
    Scene(new s02());

    Scene(new r05());
    Scene(new r03());
    Scene(new r01());
    Scene(new r02());
    Scene(new s02());

    Scene(new r05());
    Scene(new r03());
    Scene(new r01());
    Scene(new r02());
    Scene(new s02());
}
