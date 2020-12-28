#include "Game/AI/Action/actionBindParentAction.h"

namespace uking::action {

BindParentAction::BindParentAction(const InitArg& arg) : BindAction(arg) {}

BindParentAction::~BindParentAction() = default;

void BindParentAction::loadParams_() {
    BindAction::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void BindParentAction::calc_() {
    BindAction::calc_();
}

}  // namespace uking::action
