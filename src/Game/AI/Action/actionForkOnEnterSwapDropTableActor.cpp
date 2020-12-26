#include "Game/AI/Action/actionForkOnEnterSwapDropTableActor.h"

namespace uking::action {

ForkOnEnterSwapDropTableActor::ForkOnEnterSwapDropTableActor(const InitArg& arg)
    : ForkOnEnterSwapDropTableActorBase(arg) {}

ForkOnEnterSwapDropTableActor::~ForkOnEnterSwapDropTableActor() = default;

bool ForkOnEnterSwapDropTableActor::init_(sead::Heap* heap) {
    return ForkOnEnterSwapDropTableActorBase::init_(heap);
}

void ForkOnEnterSwapDropTableActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkOnEnterSwapDropTableActorBase::enter_(params);
}

void ForkOnEnterSwapDropTableActor::leave_() {
    ForkOnEnterSwapDropTableActorBase::leave_();
}

void ForkOnEnterSwapDropTableActor::loadParams_() {
    ForkOnEnterSwapDropTableActorBase::loadParams_();
    getStaticParam(&mTableName_s, "TableName");
}

void ForkOnEnterSwapDropTableActor::calc_() {
    ForkOnEnterSwapDropTableActorBase::calc_();
}

}  // namespace uking::action
