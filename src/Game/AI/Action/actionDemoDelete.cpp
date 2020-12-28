#include "Game/AI/Action/actionDemoDelete.h"

namespace uking::action {

DemoDelete::DemoDelete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoDelete::~DemoDelete() = default;

bool DemoDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoDelete::loadParams_() {}

}  // namespace uking::action
