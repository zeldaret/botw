#pragma once

#include <hostio/seadHostIONode.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resUnit.h"
#include "KingSystem/Utils/StrTreeMap.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class ControlTaskData;

class Cache : public sead::hostio::Node {
public:
    Cache();
    virtual ~Cache() = default;

    void init();
    ResourceUnit* findUnit(const ResourceUnitMapNode::KeyType& key) const;
    Handle::Status loadResource(const ControlTaskData& data);

    void eraseUnit(ResourceUnit* unit);
    void eraseUnits();

private:
    void removeUnitAndClearCache_(ResourceUnit* unit);

    // This seems to be unused.
    [[maybe_unused]] u8 _8 = 2;
    util::StrTreeMap<ResourceUnitMapNode> mMap;
};
KSYS_CHECK_SIZE_NX150(Cache, 0x18);

}  // namespace ksys::res
