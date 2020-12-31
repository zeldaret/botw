#include "Game/AI/AI/aiAssassinRoot.h"

namespace uking::ai {

AssassinRoot::AssassinRoot(const InitArg& arg) : NPCRoot(arg) {}

AssassinRoot::~AssassinRoot() = default;

bool AssassinRoot::init_(sead::Heap* heap) {
    return NPCRoot::init_(heap);
}

void AssassinRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void AssassinRoot::leave_() {
    NPCRoot::leave_();
}

void AssassinRoot::loadParams_() {
    NPCRoot::loadParams_();
    getStaticParam(&mChangeDistance_s, "ChangeDistance");
    getMapUnitParam(&mEquipItem1_m, "EquipItem1");
    getMapUnitParam(&mEquipItem2_m, "EquipItem2");
    getMapUnitParam(&mEquipItem3_m, "EquipItem3");
    getMapUnitParam(&mEquipItem4_m, "EquipItem4");
    getMapUnitParam(&mRideHorseName_m, "RideHorseName");
}

}  // namespace uking::ai
