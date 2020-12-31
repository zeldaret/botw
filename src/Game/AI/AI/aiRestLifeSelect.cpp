#include "Game/AI/AI/aiRestLifeSelect.h"

namespace uking::ai {

RestLifeSelect::RestLifeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RestLifeSelect::~RestLifeSelect() = default;

bool RestLifeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RestLifeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RestLifeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RestLifeSelect::loadParams_() {
    getStaticParam(&mLifeRatio_s, "LifeRatio");
    getStaticParam(&mIsTrgOnly_s, "IsTrgOnly");
    getStaticParam(&mIsEnter_s, "IsEnter");
}

}  // namespace uking::ai
