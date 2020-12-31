#include "Game/AI/AI/aiPartHaveSelect.h"

namespace uking::ai {

PartHaveSelect::PartHaveSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PartHaveSelect::~PartHaveSelect() = default;

bool PartHaveSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PartHaveSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PartHaveSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PartHaveSelect::loadParams_() {
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
    getStaticParam(&mPartsKey_s, "PartsKey");
}

}  // namespace uking::ai
