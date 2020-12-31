#include "Game/AI/AI/aiChemicalStayObjectRoot.h"

namespace uking::ai {

ChemicalStayObjectRoot::ChemicalStayObjectRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChemicalStayObjectRoot::~ChemicalStayObjectRoot() = default;

bool ChemicalStayObjectRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChemicalStayObjectRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ChemicalStayObjectRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChemicalStayObjectRoot::loadParams_() {
    getStaticParam(&mIsCheckDelete_s, "IsCheckDelete");
}

}  // namespace uking::ai
