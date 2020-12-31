#include "Game/AI/AI/aiSandwormStun.h"

namespace uking::ai {

SandwormStun::SandwormStun(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormStun::~SandwormStun() = default;

bool SandwormStun::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormStun::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SandwormStun::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormStun::loadParams_() {}

}  // namespace uking::ai
