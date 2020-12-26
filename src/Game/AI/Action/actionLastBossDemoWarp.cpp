#include "Game/AI/Action/actionLastBossDemoWarp.h"

namespace uking::action {

LastBossDemoWarp::LastBossDemoWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossDemoWarp::~LastBossDemoWarp() = default;

bool LastBossDemoWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossDemoWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossDemoWarp::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossDemoWarp::loadParams_() {
    getStaticParam(&mWarpTime_s, "WarpTime");
    getStaticParam(&mIsUpdateHomePos_s, "IsUpdateHomePos");
    getStaticParam(&mWarpAnchorUniqName_s, "WarpAnchorUniqName");
}

void LastBossDemoWarp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
