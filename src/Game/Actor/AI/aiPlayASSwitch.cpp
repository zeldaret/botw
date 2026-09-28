#include "Game/Actor/AI/aiPlayASSwitch.h"

namespace uking::ai {

PlayASSwitch::PlayASSwitch(const InitArg& arg) : SimpleLiftable(arg) {}

PlayASSwitch::~PlayASSwitch() = default;

bool PlayASSwitch::init_(sead::Heap* heap) {
    return SimpleLiftable::init_(heap);
}

void PlayASSwitch::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLiftable::enter_(params);
}

void PlayASSwitch::leave_() {
    SimpleLiftable::leave_();
}

void PlayASSwitch::loadParams_() {
    getStaticParam(&mIsIgnoreSameOnAS_s, "IsIgnoreSameOnAS");
    getStaticParam(&mIsIgnoreSameOffAS_s, "IsIgnoreSameOffAS");
    getStaticParam(&mOnAS_s, "OnAS");
    getStaticParam(&mOffAS_s, "OffAS");
}

}  // namespace uking::ai
