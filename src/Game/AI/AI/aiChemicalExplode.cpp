#include "Game/AI/AI/aiChemicalExplode.h"

namespace uking::ai {

ChemicalExplode::ChemicalExplode(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChemicalExplode::~ChemicalExplode() = default;

bool ChemicalExplode::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChemicalExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ChemicalExplode::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChemicalExplode::loadParams_() {}

}  // namespace uking::ai
