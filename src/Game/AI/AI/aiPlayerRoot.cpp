#include "Game/AI/AI/aiPlayerRoot.h"

namespace uking::ai {

PlayerRoot::PlayerRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void PlayerRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

}  // namespace uking::ai
