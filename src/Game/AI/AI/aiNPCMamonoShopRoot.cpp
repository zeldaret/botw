#include "Game/AI/AI/aiNPCMamonoShopRoot.h"

namespace uking::ai {

NPCMamonoShopRoot::NPCMamonoShopRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCMamonoShopRoot::~NPCMamonoShopRoot() = default;

bool NPCMamonoShopRoot::init_(sead::Heap* heap) {
    return NPCRoot::init_(heap);
}

void NPCMamonoShopRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void NPCMamonoShopRoot::leave_() {
    NPCRoot::leave_();
}

void NPCMamonoShopRoot::loadParams_() {
    NPCRoot::loadParams_();
    getMapUnitParam(&mMamonoShopPlacement_m, "MamonoShopPlacement");
}

}  // namespace uking::ai
