#include "Game/AI/AI/aiMasquaradeSubTargetSelect.h"

namespace uking::ai {

MasquaradeSubTargetSelect::MasquaradeSubTargetSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MasquaradeSubTargetSelect::~MasquaradeSubTargetSelect() = default;

bool MasquaradeSubTargetSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MasquaradeSubTargetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MasquaradeSubTargetSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MasquaradeSubTargetSelect::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
