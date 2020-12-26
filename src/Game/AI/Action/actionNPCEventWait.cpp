#include "Game/AI/Action/actionNPCEventWait.h"

namespace uking::action {

NPCEventWait::NPCEventWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCEventWait::~NPCEventWait() = default;

bool NPCEventWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCEventWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCEventWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCEventWait::loadParams_() {}

void NPCEventWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
