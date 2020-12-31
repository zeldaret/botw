#include "Game/AI/AI/aiDamageAttrSelect.h"

namespace uking::ai {

DamageAttrSelect::DamageAttrSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DamageAttrSelect::~DamageAttrSelect() = default;

bool DamageAttrSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DamageAttrSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DamageAttrSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DamageAttrSelect::loadParams_() {
    getStaticParam(&mKeyAttribute_s, "KeyAttribute");
    getStaticParam(&mOption_s, "Option");
}

}  // namespace uking::ai
