#pragma once

#include <hostio/seadHostIONode.h>
#include "KingSystem/Resource/resUnit.h"
#include "KingSystem/Utils/StrTreeMap.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

struct LoadContext;

class Cache : public sead::hostio::Node {
public:
    Cache();
    virtual ~Cache() = default;

    void init();

    ResourceUnit* findUnit(const ResourceUnitMapNode::KeyType& key) const;
    void eraseUnit(ResourceUnit* unit);

    // FIXME: return type
    s32 loadResource(const LoadContext& context);

private:
    [[maybe_unused]] u8 _8 = 2;
    util::StrTreeMap<ResourceUnitMapNode> mMap;
};
KSYS_CHECK_SIZE_NX150(Cache, 0x18);

}  // namespace ksys::res
