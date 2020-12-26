#include "Game/AI/Action/actionForkSwapPartsItemFromDropTable.h"

namespace uking::action {

ForkSwapPartsItemFromDropTable::ForkSwapPartsItemFromDropTable(const InitArg& arg) : Fork(arg) {}

ForkSwapPartsItemFromDropTable::~ForkSwapPartsItemFromDropTable() = default;

bool ForkSwapPartsItemFromDropTable::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkSwapPartsItemFromDropTable::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkSwapPartsItemFromDropTable::leave_() {
    Fork::leave_();
}

void ForkSwapPartsItemFromDropTable::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mPartsKey0_s, "PartsKey0");
    getStaticParam(&mPartsKey1_s, "PartsKey1");
    getStaticParam(&mPartsKey2_s, "PartsKey2");
    getStaticParam(&mPartsKey3_s, "PartsKey3");
    getStaticParam(&mPartsKey4_s, "PartsKey4");
}

void ForkSwapPartsItemFromDropTable::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
