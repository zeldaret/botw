#include "Game/AI/AI/aiDoChangeOneTime.h"

namespace uking::ai {

DoChangeOneTime::DoChangeOneTime(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DoChangeOneTime::~DoChangeOneTime() = default;

bool DoChangeOneTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DoChangeOneTime::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DoChangeOneTime::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DoChangeOneTime::loadParams_() {}

}  // namespace uking::ai
