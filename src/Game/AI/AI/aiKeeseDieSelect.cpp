#include "Game/AI/AI/aiKeeseDieSelect.h"

namespace uking::ai {

KeeseDieSelect::KeeseDieSelect(const InitArg& arg) : DieSelectChemShockPlus(arg) {}

KeeseDieSelect::~KeeseDieSelect() = default;

bool KeeseDieSelect::init_(sead::Heap* heap) {
    return DieSelectChemShockPlus::init_(heap);
}

void KeeseDieSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    DieSelectChemShockPlus::enter_(params);
}

void KeeseDieSelect::leave_() {
    DieSelectChemShockPlus::leave_();
}

void KeeseDieSelect::loadParams_() {
    DieSelectChemShockPlus::loadParams_();
}

}  // namespace uking::ai
