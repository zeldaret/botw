#include "Game/AI/AI/aiIceMakerBlock.h"

namespace uking::ai {

IceMakerBlock::IceMakerBlock(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

IceMakerBlock::~IceMakerBlock() = default;

bool IceMakerBlock::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void IceMakerBlock::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void IceMakerBlock::leave_() {
    ksys::act::ai::Ai::leave_();
}

void IceMakerBlock::loadParams_() {
    getStaticParam(&mSubRigidStartOffset_s, "SubRigidStartOffset");
    getStaticParam(&mSubRigidEndOffset_s, "SubRigidEndOffset");
    getStaticParam(&mSubRigidExOffset_s, "SubRigidExOffset");
}

}  // namespace uking::ai
