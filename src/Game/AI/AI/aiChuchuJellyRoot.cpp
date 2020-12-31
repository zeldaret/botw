#include "Game/AI/AI/aiChuchuJellyRoot.h"

namespace uking::ai {

ChuchuJellyRoot::ChuchuJellyRoot(const InitArg& arg) : ItemRoot(arg) {}

ChuchuJellyRoot::~ChuchuJellyRoot() = default;

bool ChuchuJellyRoot::init_(sead::Heap* heap) {
    return ItemRoot::init_(heap);
}

void ChuchuJellyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ItemRoot::enter_(params);
}

void ChuchuJellyRoot::leave_() {
    ItemRoot::leave_();
}

void ChuchuJellyRoot::loadParams_() {
    ItemRoot::loadParams_();
}

}  // namespace uking::ai
