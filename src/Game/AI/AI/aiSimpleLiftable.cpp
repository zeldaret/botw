#include "Game/AI/AI/aiSimpleLiftable.h"

namespace uking::ai {

SimpleLiftable::SimpleLiftable(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleLiftable::~SimpleLiftable() = default;

void SimpleLiftable::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

}  // namespace uking::ai
