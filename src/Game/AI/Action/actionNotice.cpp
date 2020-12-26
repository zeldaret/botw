#include "Game/AI/Action/actionNotice.h"

namespace uking::action {

Notice::Notice(const InitArg& arg) : ActionWithAS(arg) {}

Notice::~Notice() = default;

bool Notice::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void Notice::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void Notice::leave_() {
    ActionWithAS::leave_();
}

void Notice::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
}

void Notice::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
