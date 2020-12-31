#include "Game/AI/AI/aiAddNodeNodeCarried.h"

namespace uking::ai {

AddNodeNodeCarried::AddNodeNodeCarried(const InitArg& arg) : AddCarriedBase(arg) {}

AddNodeNodeCarried::~AddNodeNodeCarried() = default;

bool AddNodeNodeCarried::init_(sead::Heap* heap) {
    return AddCarriedBase::init_(heap);
}

void AddNodeNodeCarried::enter_(ksys::act::ai::InlineParamPack* params) {
    AddCarriedBase::enter_(params);
}

void AddNodeNodeCarried::leave_() {
    AddCarriedBase::leave_();
}

void AddNodeNodeCarried::loadParams_() {
    AddCarriedBase::loadParams_();
    getStaticParam(&mMyNode_s, "MyNode");
    getStaticParam(&mNodeRotOffset_s, "NodeRotOffset");
}

}  // namespace uking::ai
