#include "Game/AI/Action/actionRebound.h"

namespace uking::action {

Rebound::Rebound(const InitArg& arg) : ActionWithAS(arg) {}

Rebound::~Rebound() = default;

bool Rebound::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void Rebound::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void Rebound::leave_() {
    ActionWithAS::leave_();
}

void Rebound::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
}

void Rebound::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
