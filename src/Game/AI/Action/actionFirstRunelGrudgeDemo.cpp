#include "Game/AI/Action/actionFirstRunelGrudgeDemo.h"

namespace uking::action {

FirstRunelGrudgeDemo::FirstRunelGrudgeDemo(const InitArg& arg) : DragonPlayASForDemo(arg) {}

FirstRunelGrudgeDemo::~FirstRunelGrudgeDemo() = default;

bool FirstRunelGrudgeDemo::init_(sead::Heap* heap) {
    return DragonPlayASForDemo::init_(heap);
}

void FirstRunelGrudgeDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonPlayASForDemo::enter_(params);
}

void FirstRunelGrudgeDemo::leave_() {
    DragonPlayASForDemo::leave_();
}

void FirstRunelGrudgeDemo::loadParams_() {
    DragonPlayASForDemo::loadParams_();
}

void FirstRunelGrudgeDemo::calc_() {
    DragonPlayASForDemo::calc_();
}

}  // namespace uking::action
