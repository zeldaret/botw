#include "Game/AI/AI/aiDieSelectChemicalPlus.h"

namespace uking::ai {

DieSelectChemicalPlus::DieSelectChemicalPlus(const InitArg& arg) : DieSelect(arg) {}

DieSelectChemicalPlus::~DieSelectChemicalPlus() = default;

bool DieSelectChemicalPlus::init_(sead::Heap* heap) {
    return DieSelect::init_(heap);
}

void DieSelectChemicalPlus::enter_(ksys::act::ai::InlineParamPack* params) {
    DieSelect::enter_(params);
}

void DieSelectChemicalPlus::leave_() {
    DieSelect::leave_();
}

void DieSelectChemicalPlus::loadParams_() {
    DieSelect::loadParams_();
}

}  // namespace uking::ai
