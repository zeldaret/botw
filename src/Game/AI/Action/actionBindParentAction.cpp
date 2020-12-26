#include "Game/AI/Action/actionBindParentAction.h"

namespace uking::action {

BindParentAction::BindParentAction(const InitArg& arg) : BindAction(arg) {}

BindParentAction::~BindParentAction() = default;

bool BindParentAction::init_(sead::Heap* heap) {
    return BindAction::init_(heap);
}

void BindParentAction::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
}

void BindParentAction::leave_() {
    BindAction::leave_();
}

void BindParentAction::loadParams_() {
    BindAction::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void BindParentAction::calc_() {
    BindAction::calc_();
}

}  // namespace uking::action
