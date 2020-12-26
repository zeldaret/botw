#include "Game/AI/Action/actionGelEnemyAppear.h"

namespace uking::action {

GelEnemyAppear::GelEnemyAppear(const InitArg& arg) : Appear(arg) {}

GelEnemyAppear::~GelEnemyAppear() = default;

bool GelEnemyAppear::init_(sead::Heap* heap) {
    return Appear::init_(heap);
}

void GelEnemyAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    Appear::enter_(params);
}

void GelEnemyAppear::leave_() {
    Appear::leave_();
}

void GelEnemyAppear::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
}

void GelEnemyAppear::calc_() {
    Appear::calc_();
}

}  // namespace uking::action
