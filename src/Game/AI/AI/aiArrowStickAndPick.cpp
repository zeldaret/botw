#include "Game/AI/AI/aiArrowStickAndPick.h"

namespace uking::ai {

ArrowStickAndPick::ArrowStickAndPick(const InitArg& arg) : CommonPickedItem(arg) {}

ArrowStickAndPick::~ArrowStickAndPick() = default;

void ArrowStickAndPick::enter_(ksys::act::ai::InlineParamPack* params) {
    CommonPickedItem::enter_(params);
}

void ArrowStickAndPick::loadParams_() {
    CommonPickedItem::loadParams_();
    getDynamicParam(&mStickPos_d, "StickPos");
    getDynamicParam(&mStickPosDiv_d, "StickPosDiv");
    getDynamicParam(&mStickActor_d, "StickActor");
    getDynamicParam(&mStickBodyName_d, "StickBodyName");
}

}  // namespace uking::ai
