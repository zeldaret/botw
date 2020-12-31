#include "Game/AI/AI/aiCreationNestOnTree.h"

namespace uking::ai {

CreationNestOnTree::CreationNestOnTree(const InitArg& arg) : ItemOnTree(arg) {}

CreationNestOnTree::~CreationNestOnTree() = default;

bool CreationNestOnTree::init_(sead::Heap* heap) {
    return ItemOnTree::init_(heap);
}

void CreationNestOnTree::enter_(ksys::act::ai::InlineParamPack* params) {
    ItemOnTree::enter_(params);
}

void CreationNestOnTree::leave_() {
    ItemOnTree::leave_();
}

void CreationNestOnTree::loadParams_() {
    ItemOnTree::loadParams_();
    getStaticParam(&mActorNum_s, "ActorNum");
    getStaticParam(&mTargetEscapedRadius_s, "TargetEscapedRadius");
    getStaticParam(&mIsRemainNum_s, "IsRemainNum");
}

}  // namespace uking::ai
