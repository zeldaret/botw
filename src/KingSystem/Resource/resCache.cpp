#include "KingSystem/Resource/resCache.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Resource/resCacheCriticalSection.h"

namespace ksys::res {

Cache::Cache() = default;

void Cache::init() {}

ResourceUnit* Cache::findUnit(const util::StrTreeMapNode::KeyType& key) const {
    auto lock = sead::makeScopedLock(gCacheCriticalSection);
    ResourceUnitMapNode* node = mMap.find(key);
    return node ? node->getUnit() : nullptr;
}

void Cache::eraseUnit(ResourceUnit* unit) {
    auto lock = sead::makeScopedLock(gCacheCriticalSection);
    if (unit->isLinkedToCache()) {
        mMap.erase(unit->getCacheKey());
        unit->setIsLinkedToCache(false);
    }
}

}  // namespace ksys::res
