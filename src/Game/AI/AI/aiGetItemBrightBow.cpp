#include "Game/AI/AI/aiGetItemBrightBow.h"

namespace uking::ai {

GetItemBrightBow::GetItemBrightBow(const InitArg& arg) : GetItemNormal(arg) {}

GetItemBrightBow::~GetItemBrightBow() = default;

bool GetItemBrightBow::init_(sead::Heap* heap) {
    return GetItemNormal::init_(heap);
}

void GetItemBrightBow::enter_(ksys::act::ai::InlineParamPack* params) {
    GetItemNormal::enter_(params);
}

void GetItemBrightBow::leave_() {
    GetItemNormal::leave_();
}

void GetItemBrightBow::loadParams_() {
    GetItemNormal::loadParams_();
    getStaticParam(&mGetRadius_s, "GetRadius");
}

}  // namespace uking::ai
