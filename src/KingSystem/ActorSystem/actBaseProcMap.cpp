#include "KingSystem/ActorSystem/actBaseProcMap.h"

namespace ksys::act {

void BaseProcMapNode::add(BaseProcMapNode* node) {
    auto next = mNext;
    node->mPrev = this;
    node->mNext = next;
    mNext = node;
    if (next)
        next->mPrev = node;
}

void BaseProcMap::insert(BaseProcMapNode* node) {
    if (auto existing_node = find(node->key()))
        existing_node->add(node);
    else
        StrTreeMap::insert(node);
    node->setInserted();
}

}  // namespace ksys::act
