#include "Game/AI/Action/actionForkASTrgDeleteChild.h"

namespace uking::action {

ForkASTrgDeleteChild::ForkASTrgDeleteChild(const InitArg& arg) : ForkASTrgDelete(arg) {}

ForkASTrgDeleteChild::~ForkASTrgDeleteChild() = default;

bool ForkASTrgDeleteChild::init_(sead::Heap* heap) {
    return ForkASTrgDelete::init_(heap);
}

void ForkASTrgDeleteChild::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASTrgDelete::enter_(params);
}

void ForkASTrgDeleteChild::leave_() {
    ForkASTrgDelete::leave_();
}

void ForkASTrgDeleteChild::loadParams_() {}

void ForkASTrgDeleteChild::calc_() {
    ForkASTrgDelete::calc_();
}

}  // namespace uking::action
