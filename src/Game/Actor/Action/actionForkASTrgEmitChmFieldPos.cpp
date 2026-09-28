#include "Game/Actor/Action/actionForkASTrgEmitChmFieldPos.h"

namespace uking::action {

ForkASTrgEmitChmFieldPos::ForkASTrgEmitChmFieldPos(const InitArg& arg)
    : ForkTrgEmitChmFieldBase(arg) {}

ForkASTrgEmitChmFieldPos::~ForkASTrgEmitChmFieldPos() = default;

bool ForkASTrgEmitChmFieldPos::init_(sead::Heap* heap) {
    return ForkTrgEmitChmFieldBase::init_(heap);
}

void ForkASTrgEmitChmFieldPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTrgEmitChmFieldBase::enter_(params);
}

void ForkASTrgEmitChmFieldPos::leave_() {
    ForkTrgEmitChmFieldBase::leave_();
}

void ForkASTrgEmitChmFieldPos::loadParams_() {
    ForkTrgEmitChmFieldBase::loadParams_();
    getStaticParam(&mOffsetPos_s, "OffsetPos");
}

void ForkASTrgEmitChmFieldPos::calc_() {
    ForkTrgEmitChmFieldBase::calc_();
}

}  // namespace uking::action
