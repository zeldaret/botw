#include "Game/AI/AI/aiAssassinMiddleAzitoDlcRoot.h"

namespace uking::ai {

AssassinMiddleAzitoDlcRoot::AssassinMiddleAzitoDlcRoot(const InitArg& arg)
    : AssassinMiddleAzitoRoot(arg) {}

AssassinMiddleAzitoDlcRoot::~AssassinMiddleAzitoDlcRoot() = default;

bool AssassinMiddleAzitoDlcRoot::init_(sead::Heap* heap) {
    return AssassinMiddleAzitoRoot::init_(heap);
}

void AssassinMiddleAzitoDlcRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinMiddleAzitoRoot::enter_(params);
}

void AssassinMiddleAzitoDlcRoot::leave_() {
    AssassinMiddleAzitoRoot::leave_();
}

void AssassinMiddleAzitoDlcRoot::loadParams_() {
    AssassinMiddleAzitoRoot::loadParams_();
}

}  // namespace uking::ai
