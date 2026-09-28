#include "Game/Actor/Action/actionForbidComeback.h"

namespace uking::action {

ForbidComeback::ForbidComeback(const InitArg& arg) : AreaActionBase(arg) {}

ForbidComeback::~ForbidComeback() = default;

bool ForbidComeback::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

void ForbidComeback::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
}

void ForbidComeback::leave_() {
    AreaActionBase::leave_();
}

void ForbidComeback::loadParams_() {}

void ForbidComeback::calc_() {
    AreaActionBase::calc_();
}

}  // namespace uking::action
