#include "Game/AI/Action/actionSimpleGrabWithAS.h"

namespace uking::action {

SimpleGrabWithAS::SimpleGrabWithAS(const InitArg& arg) : SimpleGrabWithASBase(arg) {}

SimpleGrabWithAS::~SimpleGrabWithAS() = default;

bool SimpleGrabWithAS::init_(sead::Heap* heap) {
    return SimpleGrabWithASBase::init_(heap);
}

void SimpleGrabWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleGrabWithASBase::enter_(params);
}

void SimpleGrabWithAS::leave_() {
    SimpleGrabWithASBase::leave_();
}

void SimpleGrabWithAS::loadParams_() {
    SimpleGrabWithASBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void SimpleGrabWithAS::calc_() {
    SimpleGrabWithASBase::calc_();
}

}  // namespace uking::action
