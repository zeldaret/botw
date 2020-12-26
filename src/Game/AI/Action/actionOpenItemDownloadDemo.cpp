#include "Game/AI/Action/actionOpenItemDownloadDemo.h"

namespace uking::action {

OpenItemDownloadDemo::OpenItemDownloadDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenItemDownloadDemo::~OpenItemDownloadDemo() = default;

bool OpenItemDownloadDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenItemDownloadDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenItemDownloadDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenItemDownloadDemo::loadParams_() {
    getDynamicParam(&mItemType_d, "ItemType");
    getDynamicParam(&mIsEquip_d, "IsEquip");
    getDynamicParam(&mIsPowerUp_d, "IsPowerUp");
    getDynamicParam(&mIsPlayerClose_d, "IsPlayerClose");
}

void OpenItemDownloadDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
