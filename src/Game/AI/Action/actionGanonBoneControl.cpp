#include "Game/AI/Action/actionGanonBoneControl.h"

namespace uking::action {

GanonBoneControl::GanonBoneControl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonBoneControl::~GanonBoneControl() = default;

bool GanonBoneControl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonBoneControl::loadParams_() {
    getDynamicParam(&mIsBattleModeOn_d, "IsBattleModeOn");
}

}  // namespace uking::action
