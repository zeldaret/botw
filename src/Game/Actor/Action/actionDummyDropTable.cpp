#include "Game/Actor/Action/actionDummyDropTable.h"

namespace uking::action {

DummyDropTable::DummyDropTable(const InitArg& arg) : ksys::act::ai::DummyAction(arg) {}

DummyDropTable::~DummyDropTable() = default;

bool DummyDropTable::init_(sead::Heap* heap) {
    return ksys::act::ai::DummyAction::init_(heap);
}

void DummyDropTable::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::DummyAction::enter_(params);
}

void DummyDropTable::leave_() {
    ksys::act::ai::DummyAction::leave_();
}

void DummyDropTable::loadParams_() {
    ksys::act::ai::DummyAction::loadParams_();
    getMapUnitParam(&mDropTable_m, "DropTable");
}

void DummyDropTable::calc_() {
    ksys::act::ai::DummyAction::calc_();
}

}  // namespace uking::action
