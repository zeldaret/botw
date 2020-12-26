#include "Game/AI/Action/actionDemoChangeEntityNoHit.h"

namespace uking::action {

DemoChangeEntityNoHit::DemoChangeEntityNoHit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoChangeEntityNoHit::~DemoChangeEntityNoHit() = default;

bool DemoChangeEntityNoHit::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoChangeEntityNoHit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoChangeEntityNoHit::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoChangeEntityNoHit::loadParams_() {
    getStaticParam(&mSetMotionType_s, "SetMotionType");
    getStaticParam(&mIsNoHit_s, "IsNoHit");
}

void DemoChangeEntityNoHit::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
