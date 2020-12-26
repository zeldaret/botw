#include "Game/AI/Action/actionDragonPlayASForDemo.h"

namespace uking::action {

DragonPlayASForDemo::DragonPlayASForDemo(const InitArg& arg) : PlayASForDemo(arg) {}

DragonPlayASForDemo::~DragonPlayASForDemo() = default;

bool DragonPlayASForDemo::init_(sead::Heap* heap) {
    return PlayASForDemo::init_(heap);
}

void DragonPlayASForDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForDemo::enter_(params);
}

void DragonPlayASForDemo::leave_() {
    PlayASForDemo::leave_();
}

void DragonPlayASForDemo::loadParams_() {
    PlayASForDemo::loadParams_();
    getStaticParam(&mPosition_s, "Position");
    getStaticParam(&mRotate_s, "Rotate");
}

void DragonPlayASForDemo::calc_() {
    PlayASForDemo::calc_();
}

}  // namespace uking::action
