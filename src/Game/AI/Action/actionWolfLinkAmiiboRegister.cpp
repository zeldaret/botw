#include "Game/AI/Action/actionWolfLinkAmiiboRegister.h"

namespace uking::action {

WolfLinkAmiiboRegister::WolfLinkAmiiboRegister(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WolfLinkAmiiboRegister::~WolfLinkAmiiboRegister() = default;

bool WolfLinkAmiiboRegister::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WolfLinkAmiiboRegister::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WolfLinkAmiiboRegister::leave_() {
    ksys::act::ai::Action::leave_();
}

void WolfLinkAmiiboRegister::loadParams_() {
    getDynamicParam(&mSpawnFlags_d, "SpawnFlags");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void WolfLinkAmiiboRegister::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
