#include "Game/AI/AI/aiNearCreateSelect.h"

namespace uking::ai {

NearCreateSelect::NearCreateSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NearCreateSelect::~NearCreateSelect() = default;

bool NearCreateSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NearCreateSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NearCreateSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NearCreateSelect::loadParams_() {
    getMapUnitParam(&mIsNearCreate_m, "IsNearCreate");
}

}  // namespace uking::ai
