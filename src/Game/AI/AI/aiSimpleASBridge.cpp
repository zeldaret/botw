#include "Game/AI/AI/aiSimpleASBridge.h"

namespace uking::ai {

SimpleASBridge::SimpleASBridge(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleASBridge::~SimpleASBridge() = default;

bool SimpleASBridge::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SimpleASBridge::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SimpleASBridge::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleASBridge::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::ai
