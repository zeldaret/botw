#include "Game/AI/Action/actionRequestCreateHCIModel.h"

namespace uking::action {

RequestCreateHCIModel::RequestCreateHCIModel(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RequestCreateHCIModel::~RequestCreateHCIModel() = default;

bool RequestCreateHCIModel::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RequestCreateHCIModel::loadParams_() {}

}  // namespace uking::action
