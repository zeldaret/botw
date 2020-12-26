#include "Game/AI/Action/actionOpenEnduranceFloorNumber.h"

namespace uking::action {

OpenEnduranceFloorNumber::OpenEnduranceFloorNumber(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

OpenEnduranceFloorNumber::~OpenEnduranceFloorNumber() = default;

bool OpenEnduranceFloorNumber::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenEnduranceFloorNumber::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenEnduranceFloorNumber::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenEnduranceFloorNumber::loadParams_() {
    getStaticParam(&mMstxt_s, "Mstxt");
    getDynamicParam(&mSubMstxt_d, "SubMstxt");
    getDynamicParam(&mLabelName_d, "LabelName");
    getDynamicParam(&mGameDataIntFloorNum_d, "GameDataIntFloorNum");
}

void OpenEnduranceFloorNumber::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
