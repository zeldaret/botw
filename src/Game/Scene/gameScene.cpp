#include "Game/Scene/gameScene.h"
#include "KingSystem/System/StageInfo.h"

namespace uking {

bool GameScene::sIsOpenWorldDemo{};

const sead::SafeString& GameScene::getCurrentMapType() {
    return ksys::StageInfo::getCurrentMapType();
}

const sead::SafeString& GameScene::getCurrentMapName() {
    return ksys::StageInfo::getCurrentMapName();
}

}  // namespace uking
