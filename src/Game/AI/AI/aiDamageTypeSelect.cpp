#include "Game/AI/AI/aiDamageTypeSelect.h"

namespace uking::ai {

DamageTypeSelect::DamageTypeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DamageTypeSelect::~DamageTypeSelect() = default;

bool DamageTypeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DamageTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DamageTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DamageTypeSelect::loadParams_() {
    getStaticParam(&mDamageType_s, "DamageType");
}

}  // namespace uking::ai
