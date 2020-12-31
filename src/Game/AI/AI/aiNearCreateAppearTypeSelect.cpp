#include "Game/AI/AI/aiNearCreateAppearTypeSelect.h"

namespace uking::ai {

NearCreateAppearTypeSelect::NearCreateAppearTypeSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

NearCreateAppearTypeSelect::~NearCreateAppearTypeSelect() = default;

bool NearCreateAppearTypeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NearCreateAppearTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NearCreateAppearTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NearCreateAppearTypeSelect::loadParams_() {
    getMapUnitParam(&mNearCreateAppearType_m, "NearCreateAppearType");
}

}  // namespace uking::ai
