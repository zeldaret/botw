#include "Game/AI/Action/actionGameDataAddVec3.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

GameDataAddVec3::GameDataAddVec3(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataAddVec3::~GameDataAddVec3() = default;

bool GameDataAddVec3::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool GameDataAddVec3::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm) {
        setFailed();
        mFlags.set(Flag::_4);
        return false;
    }

    auto src = sead::Vector3f::zero;
    auto dst = sead::Vector3f::zero;
    if (gdm->getParam().get().getVec3f(&src, mGameDataVec3fSrcName_d)) {
        if (gdm->getParam().get().getVec3f(&dst, mGameDataVec3fDstName_d)) {
            src.x = src.x + dst.x;
            src.y = src.y + dst.y;
            src.z = src.z + dst.z;
        }
        gdm->setVec3f(src, mGameDataVec3fToName_d);
    }

    return true;
}

void GameDataAddVec3::loadParams_() {
    getDynamicParam(&mGameDataVec3fSrcName_d, "GameDataVec3fSrcName");
    getDynamicParam(&mGameDataVec3fDstName_d, "GameDataVec3fDstName");
    getDynamicParam(&mGameDataVec3fToName_d, "GameDataVec3fToName");
}

}  // namespace uking::action
