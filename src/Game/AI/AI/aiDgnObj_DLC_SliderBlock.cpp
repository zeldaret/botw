#include "Game/AI/AI/aiDgnObj_DLC_SliderBlock.h"

namespace uking::ai {

DgnObj_DLC_SliderBlock::DgnObj_DLC_SliderBlock(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DgnObj_DLC_SliderBlock::~DgnObj_DLC_SliderBlock() = default;

bool DgnObj_DLC_SliderBlock::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DgnObj_DLC_SliderBlock::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DgnObj_DLC_SliderBlock::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DgnObj_DLC_SliderBlock::loadParams_() {}

}  // namespace uking::ai
