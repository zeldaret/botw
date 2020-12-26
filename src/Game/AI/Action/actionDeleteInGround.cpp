#include "Game/AI/Action/actionDeleteInGround.h"

namespace uking::action {

DeleteInGround::DeleteInGround(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DeleteInGround::~DeleteInGround() = default;

bool DeleteInGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DeleteInGround::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DeleteInGround::leave_() {
    ksys::act::ai::Action::leave_();
}

void DeleteInGround::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

void DeleteInGround::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
