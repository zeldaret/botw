#include "Game/AI/Action/actionForbidComeback.h"

namespace uking::action {

ForbidComeback::ForbidComeback(const InitArg& arg) : AreaTagAction(arg) {}

ForbidComeback::~ForbidComeback() = default;

bool ForbidComeback::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void ForbidComeback::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void ForbidComeback::leave_() {
    AreaTagAction::leave_();
}

void ForbidComeback::loadParams_() {}

void ForbidComeback::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
