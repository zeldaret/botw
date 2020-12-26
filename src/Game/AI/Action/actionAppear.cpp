#include "Game/AI/Action/actionAppear.h"

namespace uking::action {

Appear::Appear(const InitArg& arg) : ActionWithAS(arg) {}

Appear::~Appear() = default;

bool Appear::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void Appear::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void Appear::leave_() {
    ActionWithAS::leave_();
}

void Appear::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
}

void Appear::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
