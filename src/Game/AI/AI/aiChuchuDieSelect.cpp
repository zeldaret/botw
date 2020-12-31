#include "Game/AI/AI/aiChuchuDieSelect.h"

namespace uking::ai {

ChuchuDieSelect::ChuchuDieSelect(const InitArg& arg) : DieSelectChemicalPlus(arg) {}

ChuchuDieSelect::~ChuchuDieSelect() = default;

bool ChuchuDieSelect::init_(sead::Heap* heap) {
    return DieSelectChemicalPlus::init_(heap);
}

void ChuchuDieSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    DieSelectChemicalPlus::enter_(params);
}

void ChuchuDieSelect::leave_() {
    DieSelectChemicalPlus::leave_();
}

void ChuchuDieSelect::loadParams_() {
    DieSelectChemicalPlus::loadParams_();
}

}  // namespace uking::ai
