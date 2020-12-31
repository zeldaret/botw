#include "Game/AI/AI/aiMainFieldDungeonSelect.h"

namespace uking::ai {

MainFieldDungeonSelect::MainFieldDungeonSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MainFieldDungeonSelect::~MainFieldDungeonSelect() = default;

bool MainFieldDungeonSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MainFieldDungeonSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MainFieldDungeonSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MainFieldDungeonSelect::loadParams_() {}

}  // namespace uking::ai
