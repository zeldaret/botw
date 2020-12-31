#include "Game/AI/AI/aiFirstSelect.h"

namespace uking::ai {

FirstSelect::FirstSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FirstSelect::~FirstSelect() = default;

bool FirstSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FirstSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void FirstSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FirstSelect::loadParams_() {
    getStaticParam(&mResetFromDemo_s, "ResetFromDemo");
}

}  // namespace uking::ai
