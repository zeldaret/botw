#include "Game/AI/AI/aiWolfLinkLeadToTarget.h"

namespace uking::ai {

WolfLinkLeadToTarget::WolfLinkLeadToTarget(const InitArg& arg) : LeadToTarget(arg) {}

WolfLinkLeadToTarget::~WolfLinkLeadToTarget() = default;

bool WolfLinkLeadToTarget::init_(sead::Heap* heap) {
    return LeadToTarget::init_(heap);
}

void WolfLinkLeadToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    LeadToTarget::enter_(params);
}

void WolfLinkLeadToTarget::leave_() {
    LeadToTarget::leave_();
}

void WolfLinkLeadToTarget::loadParams_() {
    LeadToTarget::loadParams_();
}

}  // namespace uking::ai
