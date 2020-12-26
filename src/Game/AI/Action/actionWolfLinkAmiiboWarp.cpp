#include "Game/AI/Action/actionWolfLinkAmiiboWarp.h"

namespace uking::action {

WolfLinkAmiiboWarp::WolfLinkAmiiboWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WolfLinkAmiiboWarp::~WolfLinkAmiiboWarp() = default;

bool WolfLinkAmiiboWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WolfLinkAmiiboWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WolfLinkAmiiboWarp::leave_() {
    ksys::act::ai::Action::leave_();
}

void WolfLinkAmiiboWarp::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void WolfLinkAmiiboWarp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
