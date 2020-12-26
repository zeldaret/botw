#include "Game/AI/Action/actionOpenDungeonTitle.h"

namespace uking::action {

OpenDungeonTitle::OpenDungeonTitle(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenDungeonTitle::~OpenDungeonTitle() = default;

bool OpenDungeonTitle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenDungeonTitle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenDungeonTitle::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenDungeonTitle::loadParams_() {
    getStaticParam(&mMstxt_s, "Mstxt");
    getDynamicParam(&mSubMstxt_d, "SubMstxt");
}

void OpenDungeonTitle::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
