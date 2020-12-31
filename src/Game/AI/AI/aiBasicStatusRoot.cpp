#include "Game/AI/AI/aiBasicStatusRoot.h"

namespace uking::ai {

BasicStatusRoot::BasicStatusRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool BasicStatusRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BasicStatusRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BasicStatusRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BasicStatusRoot::loadParams_() {}

}  // namespace uking::ai
