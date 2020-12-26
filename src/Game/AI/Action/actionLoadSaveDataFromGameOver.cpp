#include "Game/AI/Action/actionLoadSaveDataFromGameOver.h"

namespace uking::action {

LoadSaveDataFromGameOver::LoadSaveDataFromGameOver(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

LoadSaveDataFromGameOver::~LoadSaveDataFromGameOver() = default;

bool LoadSaveDataFromGameOver::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LoadSaveDataFromGameOver::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LoadSaveDataFromGameOver::leave_() {
    ksys::act::ai::Action::leave_();
}

void LoadSaveDataFromGameOver::loadParams_() {}

void LoadSaveDataFromGameOver::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
