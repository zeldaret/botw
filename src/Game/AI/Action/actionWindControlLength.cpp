#include "Game/AI/Action/actionWindControlLength.h"

namespace uking::action {

WindControlLength::WindControlLength(const InitArg& arg) : WindControl(arg) {}

WindControlLength::~WindControlLength() = default;

bool WindControlLength::init_(sead::Heap* heap) {
    return WindControl::init_(heap);
}

void WindControlLength::enter_(ksys::act::ai::InlineParamPack* params) {
    WindControl::enter_(params);
}

void WindControlLength::leave_() {
    WindControl::leave_();
}

void WindControlLength::loadParams_() {
    WindControl::loadParams_();
    getMapUnitParam(&mWindLength_m, "WindLength");
}

void WindControlLength::calc_() {
    WindControl::calc_();
}

}  // namespace uking::action
