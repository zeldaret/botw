#include "Game/AI/AI/aiFldObjDlcHeroMapRelief.h"

namespace uking::ai {

FldObjDlcHeroMapRelief::FldObjDlcHeroMapRelief(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FldObjDlcHeroMapRelief::~FldObjDlcHeroMapRelief() = default;

bool FldObjDlcHeroMapRelief::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FldObjDlcHeroMapRelief::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void FldObjDlcHeroMapRelief::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FldObjDlcHeroMapRelief::loadParams_() {
    getMapUnitParam(&mOpenFlag_m, "OpenFlag");
    getMapUnitParam(&mClearFlag_m, "ClearFlag");
}

}  // namespace uking::ai
