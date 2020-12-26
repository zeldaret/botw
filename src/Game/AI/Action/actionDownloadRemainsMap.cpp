#include "Game/AI/Action/actionDownloadRemainsMap.h"

namespace uking::action {

DownloadRemainsMap::DownloadRemainsMap(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DownloadRemainsMap::~DownloadRemainsMap() = default;

bool DownloadRemainsMap::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DownloadRemainsMap::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DownloadRemainsMap::leave_() {
    ksys::act::ai::Action::leave_();
}

void DownloadRemainsMap::loadParams_() {
    getDynamicParam(&mIsPlayerClose_d, "IsPlayerClose");
}

void DownloadRemainsMap::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
