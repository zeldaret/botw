#include "Game/Actor/Action/actionOnEnterSwapDropTableActor.h"

namespace uking::action {

OnEnterSwapDropTableActor::OnEnterSwapDropTableActor(const InitArg& arg)
    : OnEnterSwapDropTable(arg) {}

OnEnterSwapDropTableActor::~OnEnterSwapDropTableActor() = default;

bool OnEnterSwapDropTableActor::init_(sead::Heap* heap) {
    return OnEnterSwapDropTable::init_(heap);
}

void OnEnterSwapDropTableActor::enter_(ksys::act::ai::InlineParamPack* params) {
    OnEnterSwapDropTable::enter_(params);
}

void OnEnterSwapDropTableActor::leave_() {
    OnEnterSwapDropTable::leave_();
}

void OnEnterSwapDropTableActor::loadParams_() {
    OnEnterSwapDropTable::loadParams_();
    getStaticParam(&mDieType_s, "DieType");
}

void OnEnterSwapDropTableActor::calc_() {
    OnEnterSwapDropTable::calc_();
}

}  // namespace uking::action
