#include "Game/AI/AI/aiRepeatByLargeDamage.h"

namespace uking::ai {

RepeatByLargeDamage::RepeatByLargeDamage(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RepeatByLargeDamage::~RepeatByLargeDamage() = default;

bool RepeatByLargeDamage::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RepeatByLargeDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RepeatByLargeDamage::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RepeatByLargeDamage::loadParams_() {}

}  // namespace uking::ai
