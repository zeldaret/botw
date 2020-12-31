#include "Game/AI/AI/aiStole.h"

namespace uking::ai {

Stole::Stole(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void Stole::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

}  // namespace uking::ai
