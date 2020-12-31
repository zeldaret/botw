#include "Game/AI/AI/aiHorseRiddenByNPC.h"

namespace uking::ai {

HorseRiddenByNPC::HorseRiddenByNPC(const InitArg& arg) : HorseRiddenByNPCBase(arg) {}

HorseRiddenByNPC::~HorseRiddenByNPC() = default;

bool HorseRiddenByNPC::init_(sead::Heap* heap) {
    return HorseRiddenByNPCBase::init_(heap);
}

void HorseRiddenByNPC::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRiddenByNPCBase::enter_(params);
}

void HorseRiddenByNPC::leave_() {
    HorseRiddenByNPCBase::leave_();
}

void HorseRiddenByNPC::loadParams_() {
    HorseRiddenByNPCBase::loadParams_();
    getStaticParam(&mNavMeshCharacterScaleAtPrecise_s, "NavMeshCharacterScaleAtPrecise");
}

}  // namespace uking::ai
