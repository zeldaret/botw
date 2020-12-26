#include "Game/AI/Action/actionNPCWait.h"

namespace uking::action {

NPCWait::NPCWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCWait::~NPCWait() = default;

bool NPCWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCWait::loadParams_() {
    getStaticParam(&mIsIgnoreSameKey_s, "IsIgnoreSameKey");
    getStaticParam(&mASName_s, "ASName");
}

void NPCWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
