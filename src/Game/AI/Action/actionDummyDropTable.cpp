#include "Game/AI/Action/actionDummyDropTable.h"

namespace uking::action {

DummyDropTable::DummyDropTable(const InitArg& arg) : DummyAction(arg) {}

DummyDropTable::~DummyDropTable() = default;

bool DummyDropTable::init_(sead::Heap* heap) {
    return DummyAction::init_(heap);
}

void DummyDropTable::enter_(ksys::act::ai::InlineParamPack* params) {
    DummyAction::enter_(params);
}

void DummyDropTable::leave_() {
    DummyAction::leave_();
}

void DummyDropTable::loadParams_() {
    DummyAction::loadParams_();
    getMapUnitParam(&mDropTable_m, "DropTable");
}

void DummyDropTable::calc_() {
    DummyAction::calc_();
}

}  // namespace uking::action
