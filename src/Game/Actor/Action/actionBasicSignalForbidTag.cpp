#include "Game/Actor/Action/actionBasicSignalForbidTag.h"

namespace uking::action {

BasicSignalForbidTag::BasicSignalForbidTag(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BasicSignalForbidTag::~BasicSignalForbidTag() = default;

bool BasicSignalForbidTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BasicSignalForbidTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BasicSignalForbidTag::leave_() {
    ksys::act::ai::Action::leave_();
}

void BasicSignalForbidTag::loadParams_() {}

void BasicSignalForbidTag::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
