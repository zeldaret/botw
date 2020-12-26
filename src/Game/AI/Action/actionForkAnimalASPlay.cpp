#include "Game/AI/Action/actionForkAnimalASPlay.h"

namespace uking::action {

ForkAnimalASPlay::ForkAnimalASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAnimalASPlay::~ForkAnimalASPlay() = default;

bool ForkAnimalASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAnimalASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAnimalASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAnimalASPlay::loadParams_() {
    getStaticParam(&mAllowChangeableFrame_s, "AllowChangeableFrame");
    getStaticParam(&mSelectNextGearType_s, "SelectNextGearType");
    getStaticParam(&mSelectNextGear_s, "SelectNextGear");
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void ForkAnimalASPlay::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
