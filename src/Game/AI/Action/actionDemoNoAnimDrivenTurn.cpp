#include "Game/AI/Action/actionDemoNoAnimDrivenTurn.h"

namespace uking::action {

DemoNoAnimDrivenTurn::DemoNoAnimDrivenTurn(const InitArg& arg) : ForkTurn(arg) {}

DemoNoAnimDrivenTurn::~DemoNoAnimDrivenTurn() = default;

bool DemoNoAnimDrivenTurn::init_(sead::Heap* heap) {
    return ForkTurn::init_(heap);
}

void DemoNoAnimDrivenTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTurn::enter_(params);
}

void DemoNoAnimDrivenTurn::leave_() {
    ForkTurn::leave_();
}

void DemoNoAnimDrivenTurn::loadParams_() {
    ForkTurn::loadParams_();
    getDynamicParam(&mObjectId_d, "ObjectId");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

void DemoNoAnimDrivenTurn::calc_() {
    ForkTurn::calc_();
}

}  // namespace uking::action
