#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpCollidable;
struct hkpCollisionInput;
class hkpContactMgr;

class hkpContactMgrFactory : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpContactMgrFactory)

    virtual hkpContactMgr* createContactMgr(const hkpCollidable& a, const hkpCollidable& b,
                                            const hkpCollisionInput& input) = 0;
};
