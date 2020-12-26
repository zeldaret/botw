#include "Game/AI/Action/actionDungeonEntranceASPlay.h"

namespace uking::action {

DungeonEntranceASPlay::DungeonEntranceASPlay(const InitArg& arg) : NullASPlay(arg) {}

DungeonEntranceASPlay::~DungeonEntranceASPlay() = default;

bool DungeonEntranceASPlay::init_(sead::Heap* heap) {
    return NullASPlay::init_(heap);
}

void DungeonEntranceASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    NullASPlay::enter_(params);
}

void DungeonEntranceASPlay::leave_() {
    NullASPlay::leave_();
}

void DungeonEntranceASPlay::loadParams_() {
    NullASPlay::loadParams_();
    getStaticParam(&mSetDgnName_s, "SetDgnName");
}

void DungeonEntranceASPlay::calc_() {
    NullASPlay::calc_();
}

}  // namespace uking::action
