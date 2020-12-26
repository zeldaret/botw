#include "Game/AI/Action/actionRestorePlayerPosAndRotate.h"

namespace uking::action {

RestorePlayerPosAndRotate::RestorePlayerPosAndRotate(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RestorePlayerPosAndRotate::~RestorePlayerPosAndRotate() = default;

bool RestorePlayerPosAndRotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RestorePlayerPosAndRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RestorePlayerPosAndRotate::leave_() {
    ksys::act::ai::Action::leave_();
}

void RestorePlayerPosAndRotate::loadParams_() {
    getDynamicParam(&mGameDataVec3fPlayerPos_d, "GameDataVec3fPlayerPos");
    getDynamicParam(&mGameDataFloatPlayerDirectionY_d, "GameDataFloatPlayerDirectionY");
}

void RestorePlayerPosAndRotate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
