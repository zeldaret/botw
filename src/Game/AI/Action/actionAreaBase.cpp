#include "Game/AI/Action/actionAreaBase.h"

namespace uking::action {

AreaBase::AreaBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AreaBase::~AreaBase() = default;

bool AreaBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AreaBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AreaBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void AreaBase::loadParams_() {
    getMapUnitParam(&mEnableCharacterOn_m, "EnableCharacterOn");
}

void AreaBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
