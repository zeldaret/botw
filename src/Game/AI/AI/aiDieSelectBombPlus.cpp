#include "Game/AI/AI/aiDieSelectBombPlus.h"

namespace uking::ai {

DieSelectBombPlus::DieSelectBombPlus(const InitArg& arg) : DieSelect(arg) {}

DieSelectBombPlus::~DieSelectBombPlus() = default;

bool DieSelectBombPlus::init_(sead::Heap* heap) {
    return DieSelect::init_(heap);
}

void DieSelectBombPlus::enter_(ksys::act::ai::InlineParamPack* params) {
    DieSelect::enter_(params);
}

void DieSelectBombPlus::leave_() {
    DieSelect::leave_();
}

void DieSelectBombPlus::loadParams_() {
    DieSelect::loadParams_();
}

}  // namespace uking::ai
