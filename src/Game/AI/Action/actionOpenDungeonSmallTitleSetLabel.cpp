#include "Game/AI/Action/actionOpenDungeonSmallTitleSetLabel.h"

namespace uking::action {

OpenDungeonSmallTitleSetLabel::OpenDungeonSmallTitleSetLabel(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

OpenDungeonSmallTitleSetLabel::~OpenDungeonSmallTitleSetLabel() = default;

bool OpenDungeonSmallTitleSetLabel::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenDungeonSmallTitleSetLabel::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenDungeonSmallTitleSetLabel::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenDungeonSmallTitleSetLabel::loadParams_() {
    getStaticParam(&mMstxt_s, "Mstxt");
    getDynamicParam(&mSubMstxt_d, "SubMstxt");
    getDynamicParam(&mLabelName_d, "LabelName");
}

void OpenDungeonSmallTitleSetLabel::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
