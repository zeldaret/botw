#include "Game/AI/Action/actionAnmTimingBackWalk.h"

namespace uking::action {

AnmTimingBackWalk::AnmTimingBackWalk(const InitArg& arg) : BackWalkWithAS(arg) {}

AnmTimingBackWalk::~AnmTimingBackWalk() = default;

bool AnmTimingBackWalk::init_(sead::Heap* heap) {
    return BackWalkWithAS::init_(heap);
}

void AnmTimingBackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkWithAS::enter_(params);
}

void AnmTimingBackWalk::leave_() {
    BackWalkWithAS::leave_();
}

void AnmTimingBackWalk::loadParams_() {
    BackWalkWithAS::loadParams_();
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
}

void AnmTimingBackWalk::calc_() {
    BackWalkWithAS::calc_();
}

}  // namespace uking::action
