#include "Game/AI/Action/actionOffMiss.h"

namespace uking::action {

OffMiss::OffMiss(const InitArg& arg) : Off(arg) {}

OffMiss::~OffMiss() = default;

bool OffMiss::init_(sead::Heap* heap) {
    return Off::init_(heap);
}

void OffMiss::enter_(ksys::act::ai::InlineParamPack* params) {
    Off::enter_(params);
}

void OffMiss::leave_() {
    Off::leave_();
}

void OffMiss::loadParams_() {
    Off::loadParams_();
}

void OffMiss::calc_() {
    Off::calc_();
}

}  // namespace uking::action
