#include "Game/AI/Action/actionForkASTrgForceDirAerialTurn.h"

namespace uking::action {

ForkASTrgForceDirAerialTurn::ForkASTrgForceDirAerialTurn(const InitArg& arg)
    : ForkASTrgAerialTurn(arg) {}

ForkASTrgForceDirAerialTurn::~ForkASTrgForceDirAerialTurn() = default;

bool ForkASTrgForceDirAerialTurn::init_(sead::Heap* heap) {
    return ForkASTrgAerialTurn::init_(heap);
}

void ForkASTrgForceDirAerialTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASTrgAerialTurn::enter_(params);
}

void ForkASTrgForceDirAerialTurn::leave_() {
    ForkASTrgAerialTurn::leave_();
}

void ForkASTrgForceDirAerialTurn::loadParams_() {
    ForkASTrgAerialTurn::loadParams_();
    getStaticParam(&mDir_s, "Dir");
}

void ForkASTrgForceDirAerialTurn::calc_() {
    ForkASTrgAerialTurn::calc_();
}

}  // namespace uking::action
