#include "Game/AI/AI/aiKeyLockedShutter.h"

namespace uking::ai {

KeyLockedShutter::KeyLockedShutter(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KeyLockedShutter::~KeyLockedShutter() = default;

void KeyLockedShutter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void KeyLockedShutter::loadParams_() {}

}  // namespace uking::ai
