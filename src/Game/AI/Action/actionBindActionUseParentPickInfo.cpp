#include "Game/AI/Action/actionBindActionUseParentPickInfo.h"

namespace uking::action {

BindActionUseParentPickInfo::BindActionUseParentPickInfo(const InitArg& arg)
    : BindActionForManyActor(arg) {}

BindActionUseParentPickInfo::~BindActionUseParentPickInfo() = default;

bool BindActionUseParentPickInfo::init_(sead::Heap* heap) {
    return BindActionForManyActor::init_(heap);
}

void BindActionUseParentPickInfo::enter_(ksys::act::ai::InlineParamPack* params) {
    BindActionForManyActor::enter_(params);
}

void BindActionUseParentPickInfo::leave_() {
    BindActionForManyActor::leave_();
}

void BindActionUseParentPickInfo::loadParams_() {
    BindActionForManyActor::loadParams_();
}

void BindActionUseParentPickInfo::calc_() {
    BindActionForManyActor::calc_();
}

}  // namespace uking::action
