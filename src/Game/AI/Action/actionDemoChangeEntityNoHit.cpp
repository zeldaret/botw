#include "Game/AI/Action/actionDemoChangeEntityNoHit.h"

namespace uking::action {

DemoChangeEntityNoHit::DemoChangeEntityNoHit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoChangeEntityNoHit::~DemoChangeEntityNoHit() = default;

bool DemoChangeEntityNoHit::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoChangeEntityNoHit::loadParams_() {
    getStaticParam(&mSetMotionType_s, "SetMotionType");
    getStaticParam(&mIsNoHit_s, "IsNoHit");
}

}  // namespace uking::action
