#include "Game/AI/AI/aiAddCarried.h"

namespace uking::ai {

AddCarried::AddCarried(const InitArg& arg) : AddCarriedBase(arg) {}

AddCarried::~AddCarried() = default;

bool AddCarried::init_(sead::Heap* heap) {
    return AddCarriedBase::init_(heap);
}

void AddCarried::enter_(ksys::act::ai::InlineParamPack* params) {
    AddCarriedBase::enter_(params);
}

void AddCarried::leave_() {
    AddCarriedBase::leave_();
}

void AddCarried::loadParams_() {
    AddCarriedBase::loadParams_();
}

}  // namespace uking::ai
