#include "Game/AI/Action/actionStorePlayerPosAndRotate.h"

namespace uking::action {

StorePlayerPosAndRotate::StorePlayerPosAndRotate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StorePlayerPosAndRotate::~StorePlayerPosAndRotate() = default;

bool StorePlayerPosAndRotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StorePlayerPosAndRotate::loadParams_() {
    getDynamicParam(&mGameDataVec3fPlayerPos_d, "GameDataVec3fPlayerPos");
    getDynamicParam(&mGameDataFloatPlayerDirectionY_d, "GameDataFloatPlayerDirectionY");
}

}  // namespace uking::action
