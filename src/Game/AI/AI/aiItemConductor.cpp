#include "Game/AI/AI/aiItemConductor.h"

namespace uking::ai {

ItemConductor::ItemConductor(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ItemConductor::~ItemConductor() = default;

void ItemConductor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ItemConductor::loadParams_() {}

}  // namespace uking::ai
