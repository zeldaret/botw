#include "Game/AI/Action/actionGameDataAddFloat.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

GameDataAddFloat::GameDataAddFloat(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataAddFloat::~GameDataAddFloat() = default;

bool GameDataAddFloat::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool GameDataAddFloat::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm) {
        setFailed();
        mFlags.set(Flag::_4);
        return false;
    }

    f32 src = 0.0;
    f32 dst = 0.0;
    if (gdm->getParam().get().getF32(&src, mGameDataFloatSrcName_d)) {
        if (gdm->getParam().get().getF32(&dst, mGameDataFloatDstName_d))
            src += dst;
        gdm->setF32(src, mGameDataFloatToName_d);
    }

    return true;
}

void GameDataAddFloat::loadParams_() {
    getDynamicParam(&mGameDataFloatSrcName_d, "GameDataFloatSrcName");
    getDynamicParam(&mGameDataFloatDstName_d, "GameDataFloatDstName");
    getDynamicParam(&mGameDataFloatToName_d, "GameDataFloatToName");
}

}  // namespace uking::action
