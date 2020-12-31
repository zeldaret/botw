#include "Game/AI/AI/aiStalHeadLifted.h"

namespace uking::ai {

StalHeadLifted::StalHeadLifted(const InitArg& arg) : Lifted(arg) {}

StalHeadLifted::~StalHeadLifted() = default;

bool StalHeadLifted::init_(sead::Heap* heap) {
    return Lifted::init_(heap);
}

void StalHeadLifted::enter_(ksys::act::ai::InlineParamPack* params) {
    Lifted::enter_(params);
}

void StalHeadLifted::leave_() {
    Lifted::leave_();
}

void StalHeadLifted::loadParams_() {
    Lifted::loadParams_();
    getStaticParam(&mEscapeSpeed_s, "EscapeSpeed");
    getStaticParam(&mEscapeDir_s, "EscapeDir");
}

}  // namespace uking::ai
