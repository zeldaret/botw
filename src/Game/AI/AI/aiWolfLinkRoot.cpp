#include "Game/AI/AI/aiWolfLinkRoot.h"

namespace uking::ai {

WolfLinkRoot::WolfLinkRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkRoot::~WolfLinkRoot() = default;

bool WolfLinkRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkRoot::loadParams_() {}

}  // namespace uking::ai
