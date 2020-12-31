#include "Game/AI/AI/aiTargetPickedItem.h"

namespace uking::ai {

TargetPickedItem::TargetPickedItem(const InitArg& arg) : CommonPickedItem(arg) {}

TargetPickedItem::~TargetPickedItem() = default;

bool TargetPickedItem::init_(sead::Heap* heap) {
    return CommonPickedItem::init_(heap);
}

void TargetPickedItem::enter_(ksys::act::ai::InlineParamPack* params) {
    CommonPickedItem::enter_(params);
}

void TargetPickedItem::leave_() {
    CommonPickedItem::leave_();
}

void TargetPickedItem::loadParams_() {
    CommonPickedItem::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
