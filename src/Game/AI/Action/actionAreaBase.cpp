#include "Game/AI/Action/actionAreaBase.h"

namespace uking::action {

AreaBase::AreaBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void AreaBase::loadParams_() {
    getMapUnitParam(&mEnableCharacterOn_m, "EnableCharacterOn");
}

void AreaBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
