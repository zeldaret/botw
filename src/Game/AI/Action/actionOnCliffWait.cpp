#include "Game/AI/Action/actionOnCliffWait.h"

namespace uking::action {

OnCliffWait::OnCliffWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OnCliffWait::~OnCliffWait() = default;

bool OnCliffWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OnCliffWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OnCliffWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void OnCliffWait::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

void OnCliffWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
