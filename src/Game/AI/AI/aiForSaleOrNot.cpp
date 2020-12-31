#include "Game/AI/AI/aiForSaleOrNot.h"

namespace uking::ai {

ForSaleOrNot::ForSaleOrNot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ForSaleOrNot::~ForSaleOrNot() = default;

bool ForSaleOrNot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ForSaleOrNot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ForSaleOrNot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ForSaleOrNot::loadParams_() {}

}  // namespace uking::ai
