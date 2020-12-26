#include "Game/AI/Action/actionEatWithAS.h"

namespace uking::action {

EatWithAS::EatWithAS(const InitArg& arg) : Eat(arg) {}

EatWithAS::~EatWithAS() = default;

bool EatWithAS::init_(sead::Heap* heap) {
    return Eat::init_(heap);
}

void EatWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    Eat::enter_(params);
}

void EatWithAS::leave_() {
    Eat::leave_();
}

void EatWithAS::loadParams_() {
    Eat::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void EatWithAS::calc_() {
    Eat::calc_();
}

}  // namespace uking::action
