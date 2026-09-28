#include "Game/Actor/AI/aiAddViewTarget.h"

namespace uking::ai {

AddViewTarget::AddViewTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AddViewTarget::~AddViewTarget() = default;

bool AddViewTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddViewTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AddViewTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AddViewTarget::loadParams_() {}

}  // namespace uking::ai
