#include "Game/AI/AI/aiDieSelectChemShockPlus.h"

namespace uking::ai {

DieSelectChemShockPlus::DieSelectChemShockPlus(const InitArg& arg) : DieSelectChemicalPlus(arg) {}

DieSelectChemShockPlus::~DieSelectChemShockPlus() = default;

bool DieSelectChemShockPlus::init_(sead::Heap* heap) {
    return DieSelectChemicalPlus::init_(heap);
}

void DieSelectChemShockPlus::enter_(ksys::act::ai::InlineParamPack* params) {
    DieSelectChemicalPlus::enter_(params);
}

void DieSelectChemShockPlus::leave_() {
    DieSelectChemicalPlus::leave_();
}

void DieSelectChemShockPlus::loadParams_() {
    DieSelectChemicalPlus::loadParams_();
}

}  // namespace uking::ai
