#include "Game/AI/Action/actionToCDungeon.h"

namespace uking::action {

ToCDungeon::ToCDungeon(const InitArg& arg) : ChangeSceneBase(arg) {}

ToCDungeon::~ToCDungeon() = default;

bool ToCDungeon::init_(sead::Heap* heap) {
    return ChangeSceneBase::init_(heap);
}

void ToCDungeon::enter_(ksys::act::ai::InlineParamPack* params) {
    ChangeSceneBase::enter_(params);
}

void ToCDungeon::leave_() {
    ChangeSceneBase::leave_();
}

void ToCDungeon::loadParams_() {
    ChangeSceneBase::loadParams_();
}

void ToCDungeon::calc_() {
    ChangeSceneBase::calc_();
}

}  // namespace uking::action
