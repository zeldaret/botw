#include "Game/AI/AI/aiAssassinMagicTgtSelect.h"

namespace uking::ai {

AssassinMagicTgtSelect::AssassinMagicTgtSelect(const InitArg& arg) : TargetInAreaSelect(arg) {}

AssassinMagicTgtSelect::~AssassinMagicTgtSelect() = default;

bool AssassinMagicTgtSelect::init_(sead::Heap* heap) {
    return TargetInAreaSelect::init_(heap);
}

void AssassinMagicTgtSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetInAreaSelect::enter_(params);
}

void AssassinMagicTgtSelect::leave_() {
    TargetInAreaSelect::leave_();
}

void AssassinMagicTgtSelect::loadParams_() {
    TargetInAreaSelect::loadParams_();
    getStaticParam(&mHeight_s, "Height");
}

}  // namespace uking::ai
