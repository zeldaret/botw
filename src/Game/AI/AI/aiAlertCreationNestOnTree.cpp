#include "Game/AI/AI/aiAlertCreationNestOnTree.h"

namespace uking::ai {

AlertCreationNestOnTree::AlertCreationNestOnTree(const InitArg& arg) : CreationNestOnTree(arg) {}

AlertCreationNestOnTree::~AlertCreationNestOnTree() = default;

bool AlertCreationNestOnTree::init_(sead::Heap* heap) {
    return CreationNestOnTree::init_(heap);
}

void AlertCreationNestOnTree::enter_(ksys::act::ai::InlineParamPack* params) {
    CreationNestOnTree::enter_(params);
}

void AlertCreationNestOnTree::leave_() {
    CreationNestOnTree::leave_();
}

void AlertCreationNestOnTree::loadParams_() {
    CreationNestOnTree::loadParams_();
    getStaticParam(&mCreateIntervalTime_s, "CreateIntervalTime");
}

}  // namespace uking::ai
