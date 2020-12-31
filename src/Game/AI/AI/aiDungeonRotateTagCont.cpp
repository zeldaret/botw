#include "Game/AI/AI/aiDungeonRotateTagCont.h"

namespace uking::ai {

DungeonRotateTagCont::DungeonRotateTagCont(const InitArg& arg) : DungeonRotateTagInOrder(arg) {}

DungeonRotateTagCont::~DungeonRotateTagCont() = default;

bool DungeonRotateTagCont::init_(sead::Heap* heap) {
    return DungeonRotateTagInOrder::init_(heap);
}

void DungeonRotateTagCont::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateTagInOrder::enter_(params);
}

void DungeonRotateTagCont::leave_() {
    DungeonRotateTagInOrder::leave_();
}

void DungeonRotateTagCont::loadParams_() {
    DungeonRotateTagInOrder::loadParams_();
    getAITreeVariable(&mIsContinueRotateOrMove_a, "IsContinueRotateOrMove");
}

}  // namespace uking::ai
