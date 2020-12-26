#include "Game/AI/Action/actionShiekSensorPlusDownloadDemo.h"

namespace uking::action {

ShiekSensorPlusDownloadDemo::ShiekSensorPlusDownloadDemo(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ShiekSensorPlusDownloadDemo::~ShiekSensorPlusDownloadDemo() = default;

bool ShiekSensorPlusDownloadDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShiekSensorPlusDownloadDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ShiekSensorPlusDownloadDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void ShiekSensorPlusDownloadDemo::loadParams_() {
    getDynamicParam(&mIsPlayerClose_d, "IsPlayerClose");
}

void ShiekSensorPlusDownloadDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
