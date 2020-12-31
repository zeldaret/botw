#include "Game/AI/AI/aiFromPopPoolDamageSelect.h"

namespace uking::ai {

FromPopPoolDamageSelect::FromPopPoolDamageSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FromPopPoolDamageSelect::~FromPopPoolDamageSelect() = default;

bool FromPopPoolDamageSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FromPopPoolDamageSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void FromPopPoolDamageSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FromPopPoolDamageSelect::loadParams_() {}

}  // namespace uking::ai
