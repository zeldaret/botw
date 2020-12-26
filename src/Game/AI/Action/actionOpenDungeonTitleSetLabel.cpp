#include "Game/AI/Action/actionOpenDungeonTitleSetLabel.h"

namespace uking::action {

OpenDungeonTitleSetLabel::OpenDungeonTitleSetLabel(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

OpenDungeonTitleSetLabel::~OpenDungeonTitleSetLabel() = default;

bool OpenDungeonTitleSetLabel::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenDungeonTitleSetLabel::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenDungeonTitleSetLabel::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenDungeonTitleSetLabel::loadParams_() {
    getStaticParam(&mMstxt_s, "Mstxt");
    getDynamicParam(&mSubMstxt_d, "SubMstxt");
    getDynamicParam(&mLabelName_d, "LabelName");
}

void OpenDungeonTitleSetLabel::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
