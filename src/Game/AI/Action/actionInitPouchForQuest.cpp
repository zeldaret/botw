#include "Game/AI/Action/actionInitPouchForQuest.h"

namespace uking::action {

InitPouchForQuest::InitPouchForQuest(const InitArg& arg) : ksys::act::ai::Action(arg) {}

InitPouchForQuest::~InitPouchForQuest() = default;

bool InitPouchForQuest::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void InitPouchForQuest::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void InitPouchForQuest::leave_() {
    ksys::act::ai::Action::leave_();
}

void InitPouchForQuest::loadParams_() {}

void InitPouchForQuest::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
