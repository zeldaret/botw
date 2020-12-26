#include "Game/AI/Action/actionOnEnterSwapDropTableActor.h"

namespace uking::action {

OnEnterSwapDropTableActor::OnEnterSwapDropTableActor(const InitArg& arg)
    : ForkOnEnterSwapDropTableActor(arg) {}

OnEnterSwapDropTableActor::~OnEnterSwapDropTableActor() = default;

bool OnEnterSwapDropTableActor::init_(sead::Heap* heap) {
    return ForkOnEnterSwapDropTableActor::init_(heap);
}

void OnEnterSwapDropTableActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkOnEnterSwapDropTableActor::enter_(params);
}

void OnEnterSwapDropTableActor::leave_() {
    ForkOnEnterSwapDropTableActor::leave_();
}

void OnEnterSwapDropTableActor::loadParams_() {
    ForkOnEnterSwapDropTableActor::loadParams_();
    getStaticParam(&mDieType_s, "DieType");
}

void OnEnterSwapDropTableActor::calc_() {
    ForkOnEnterSwapDropTableActor::calc_();
}

}  // namespace uking::action
