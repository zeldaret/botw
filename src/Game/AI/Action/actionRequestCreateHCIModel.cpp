#include "Game/AI/Action/actionRequestCreateHCIModel.h"

namespace uking::action {

RequestCreateHCIModel::RequestCreateHCIModel(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RequestCreateHCIModel::~RequestCreateHCIModel() = default;

bool RequestCreateHCIModel::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RequestCreateHCIModel::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RequestCreateHCIModel::leave_() {
    ksys::act::ai::Action::leave_();
}

void RequestCreateHCIModel::loadParams_() {}

void RequestCreateHCIModel::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
