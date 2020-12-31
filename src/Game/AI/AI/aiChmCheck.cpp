#include "Game/AI/AI/aiChmCheck.h"

namespace uking::ai {

ChmCheck::ChmCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChmCheck::~ChmCheck() = default;

bool ChmCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChmCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ChmCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChmCheck::loadParams_() {
    getStaticParam(&mChmType_s, "ChmType");
}

}  // namespace uking::ai
