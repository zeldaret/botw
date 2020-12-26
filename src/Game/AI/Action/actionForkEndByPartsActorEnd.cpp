#include "Game/AI/Action/actionForkEndByPartsActorEnd.h"

namespace uking::action {

ForkEndByPartsActorEnd::ForkEndByPartsActorEnd(const InitArg& arg) : Fork(arg) {}

ForkEndByPartsActorEnd::~ForkEndByPartsActorEnd() = default;

bool ForkEndByPartsActorEnd::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkEndByPartsActorEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkEndByPartsActorEnd::leave_() {
    Fork::leave_();
}

void ForkEndByPartsActorEnd::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mPartsKey_s, "PartsKey");
}

void ForkEndByPartsActorEnd::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
