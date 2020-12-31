#include "Game/AI/AI/aiCommonPickedItem.h"

namespace uking::ai {

CommonPickedItem::CommonPickedItem(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CommonPickedItem::~CommonPickedItem() = default;

bool CommonPickedItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CommonPickedItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CommonPickedItem::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CommonPickedItem::loadParams_() {
    getStaticParam(&mCanGetOnBurning_s, "CanGetOnBurning");
    getStaticParam(&mIsControlNoticeDo_s, "IsControlNoticeDo");
    getStaticParam(&mGetAttKeyName_s, "GetAttKeyName");
    getMapUnitParam(&mIsPlayerPut_m, "IsPlayerPut");
    getMapUnitParam(&mDropTable_m, "DropTable");
    getMapUnitParam(&mDropActor_m, "DropActor");
    getAITreeVariable(&mGetNumLeft_a, "GetNumLeft");
}

}  // namespace uking::ai
