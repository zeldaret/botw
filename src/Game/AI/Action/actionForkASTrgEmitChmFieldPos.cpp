#include "Game/AI/Action/actionForkASTrgEmitChmFieldPos.h"

namespace uking::action {

ForkASTrgEmitChmFieldPos::ForkASTrgEmitChmFieldPos(const InitArg& arg) : ForkEmitChmField(arg) {}

ForkASTrgEmitChmFieldPos::~ForkASTrgEmitChmFieldPos() = default;

bool ForkASTrgEmitChmFieldPos::init_(sead::Heap* heap) {
    return ForkEmitChmField::init_(heap);
}

void ForkASTrgEmitChmFieldPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitChmField::enter_(params);
}

void ForkASTrgEmitChmFieldPos::leave_() {
    ForkEmitChmField::leave_();
}

void ForkASTrgEmitChmFieldPos::loadParams_() {
    ForkEmitChmField::loadParams_();
    getStaticParam(&mOffsetPos_s, "OffsetPos");
}

void ForkASTrgEmitChmFieldPos::calc_() {
    ForkEmitChmField::calc_();
}

}  // namespace uking::action
