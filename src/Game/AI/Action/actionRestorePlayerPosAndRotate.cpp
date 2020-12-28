#include "Game/AI/Action/actionRestorePlayerPosAndRotate.h"

namespace uking::action {

RestorePlayerPosAndRotate::RestorePlayerPosAndRotate(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RestorePlayerPosAndRotate::~RestorePlayerPosAndRotate() = default;

bool RestorePlayerPosAndRotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RestorePlayerPosAndRotate::loadParams_() {
    getDynamicParam(&mGameDataVec3fPlayerPos_d, "GameDataVec3fPlayerPos");
    getDynamicParam(&mGameDataFloatPlayerDirectionY_d, "GameDataFloatPlayerDirectionY");
}

}  // namespace uking::action
