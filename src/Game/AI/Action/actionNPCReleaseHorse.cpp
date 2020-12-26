#include "Game/AI/Action/actionNPCReleaseHorse.h"

namespace uking::action {

NPCReleaseHorse::NPCReleaseHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCReleaseHorse::~NPCReleaseHorse() = default;

bool NPCReleaseHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCReleaseHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCReleaseHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCReleaseHorse::loadParams_() {}

void NPCReleaseHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
