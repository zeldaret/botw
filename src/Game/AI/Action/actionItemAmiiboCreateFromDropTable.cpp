#include "Game/AI/Action/actionItemAmiiboCreateFromDropTable.h"

namespace uking::action {

ItemAmiiboCreateFromDropTable::ItemAmiiboCreateFromDropTable(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ItemAmiiboCreateFromDropTable::~ItemAmiiboCreateFromDropTable() = default;

bool ItemAmiiboCreateFromDropTable::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ItemAmiiboCreateFromDropTable::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ItemAmiiboCreateFromDropTable::leave_() {
    ksys::act::ai::Action::leave_();
}

void ItemAmiiboCreateFromDropTable::loadParams_() {
    getStaticParam(&mCreateInterval_s, "CreateInterval");
    getStaticParam(&mClearSealNum_s, "ClearSealNum");
    getStaticParam(&mHitRateAdjustStart_s, "HitRateAdjustStart");
    getStaticParam(&mHitRateAdjustEnd_s, "HitRateAdjustEnd");
    getStaticParam(&mCreateArea_s, "CreateArea");
    getStaticParam(&mBigHitRate1st_s, "BigHitRate1st");
    getStaticParam(&mBigHitRate2nd_s, "BigHitRate2nd");
    getStaticParam(&mBigHitRate3rd_s, "BigHitRate3rd");
    getStaticParam(&mGreatHitRate1st_s, "GreatHitRate1st");
    getStaticParam(&mGreatHitRate2nd_s, "GreatHitRate2nd");
    getStaticParam(&mGreatHitRate3rd_s, "GreatHitRate3rd");
    getStaticParam(&mDropNumRate1st_s, "DropNumRate1st");
    getStaticParam(&mDropNumRate2nd_s, "DropNumRate2nd");
    getStaticParam(&mDropNumRate3rd_s, "DropNumRate3rd");
    getStaticParam(&mSmallHitRate1st_s, "SmallHitRate1st");
    getStaticParam(&mSmallHitRate2nd_s, "SmallHitRate2nd");
    getStaticParam(&mSmallHitRate3rd_s, "SmallHitRate3rd");
    getStaticParam(&mPairActor_0_s, "PairActor_0");
    getStaticParam(&mPairActor_1_s, "PairActor_1");
    getStaticParam(&mPairActor_2_s, "PairActor_2");
    getStaticParam(&mFlagActor_0_s, "FlagActor_0");
    getStaticParam(&mFlagActor_1_s, "FlagActor_1");
    getStaticParam(&mFlagActor_2_s, "FlagActor_2");
    getStaticParam(&mNotFlagActor_0_s, "NotFlagActor_0");
    getStaticParam(&mNotFlagActor_1_s, "NotFlagActor_1");
    getStaticParam(&mCreateOffset_s, "CreateOffset");
    // FIXME: CALL AI_Action_ItemAmiiboCreateFromDropTable__parsePairActor @ 0x71001bfa64
    // FIXME: CALL AI_Action_ItemAmiiboCreateFromDropTable__parsePairActor @ 0x71001bfa64
    // FIXME: CALL AI_Action_ItemAmiiboCreateFromDropTable__parsePairActor @ 0x71001bfa64
    // FIXME: CALL AI_Action_ItemAmiiboCreateFromDropTable__parseFlagActor @ 0x71001bfe54
    // FIXME: CALL AI_Action_ItemAmiiboCreateFromDropTable__parseFlagActor @ 0x71001bfe54
    // FIXME: CALL AI_Action_ItemAmiiboCreateFromDropTable__parseFlagActor @ 0x71001bfe54
    // FIXME: CALL AI_Action_ItemAmiiboCreateFromDropTable__parseFlagActor @ 0x71001bfe54
    // FIXME: CALL AI_Action_ItemAmiiboCreateFromDropTable__parseFlagActor @ 0x71001bfe54
}

void ItemAmiiboCreateFromDropTable::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
