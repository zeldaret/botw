#include "Game/AI/Action/actionSmallDamage.h"

namespace uking::action {

SmallDamage::SmallDamage(const InitArg& arg) : SmallDamageBase(arg) {}

void SmallDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamageBase::enter_(params);
}

}  // namespace uking::action
