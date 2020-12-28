#include "Game/AI/Action/actionStartMapOpenDemo.h"

namespace uking::action {

StartMapOpenDemo::StartMapOpenDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StartMapOpenDemo::~StartMapOpenDemo() = default;

bool StartMapOpenDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StartMapOpenDemo::loadParams_() {
    getDynamicParam(&mIsPlayerClose_d, "IsPlayerClose");
}

}  // namespace uking::action
