#include "Game/AI/AI/aiMimicFlagSelect.h"

namespace uking::ai {

MimicFlagSelect::MimicFlagSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MimicFlagSelect::~MimicFlagSelect() = default;

bool MimicFlagSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MimicFlagSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MimicFlagSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MimicFlagSelect::loadParams_() {
    getMapUnitParam(&mIsMimicry_m, "IsMimicry");
}

}  // namespace uking::ai
