#include "Game/Actor/Action/actionOnEnterSwapDropTable.h"

namespace uking::action {

OnEnterSwapDropTable::OnEnterSwapDropTable(const InitArg& arg) : OnEnterSwapActorBase(arg) {}

OnEnterSwapDropTable::~OnEnterSwapDropTable() = default;

bool OnEnterSwapDropTable::init_(sead::Heap* heap) {
    return OnEnterSwapActorBase::init_(heap);
}

void OnEnterSwapDropTable::enter_(ksys::act::ai::InlineParamPack* params) {
    OnEnterSwapActorBase::enter_(params);
}

void OnEnterSwapDropTable::leave_() {
    OnEnterSwapActorBase::leave_();
}

void OnEnterSwapDropTable::loadParams_() {
    OnEnterSwapActorBase::loadParams_();
    getStaticParam(&mTableName_s, "TableName");
}

void OnEnterSwapDropTable::calc_() {
    OnEnterSwapActorBase::calc_();
}

}  // namespace uking::action
