#include "Game/AI/AI/aiStalPartsHasSelect.h"

namespace uking::ai {

StalPartsHasSelect::StalPartsHasSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalPartsHasSelect::~StalPartsHasSelect() = default;

bool StalPartsHasSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalPartsHasSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalPartsHasSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalPartsHasSelect::loadParams_() {
    getStaticParam(&mPartsID_s, "PartsID");
}

}  // namespace uking::ai
