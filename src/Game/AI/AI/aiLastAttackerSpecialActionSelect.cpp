#include "Game/AI/AI/aiLastAttackerSpecialActionSelect.h"

namespace uking::ai {

LastAttackerSpecialActionSelect::LastAttackerSpecialActionSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

LastAttackerSpecialActionSelect::~LastAttackerSpecialActionSelect() = default;

bool LastAttackerSpecialActionSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastAttackerSpecialActionSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LastAttackerSpecialActionSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastAttackerSpecialActionSelect::loadParams_() {
    getStaticParam(&mIsAngerActorSpecial_s, "IsAngerActorSpecial");
}

}  // namespace uking::ai
