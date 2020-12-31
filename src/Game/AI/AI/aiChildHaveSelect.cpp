#include "Game/AI/AI/aiChildHaveSelect.h"

namespace uking::ai {

ChildHaveSelect::ChildHaveSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChildHaveSelect::~ChildHaveSelect() = default;

bool ChildHaveSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChildHaveSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ChildHaveSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChildHaveSelect::loadParams_() {
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
}

}  // namespace uking::ai
