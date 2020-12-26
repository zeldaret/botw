#include "Game/AI/Action/actionDirectToWindDirection.h"

namespace uking::action {

DirectToWindDirection::DirectToWindDirection(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DirectToWindDirection::~DirectToWindDirection() = default;

bool DirectToWindDirection::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DirectToWindDirection::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DirectToWindDirection::leave_() {
    ksys::act::ai::Action::leave_();
}

void DirectToWindDirection::loadParams_() {
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mRotMax_s, "RotMax");
    getStaticParam(&mFrontDir_s, "FrontDir");
    getStaticParam(&mUpDir_s, "UpDir");
}

void DirectToWindDirection::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
