#pragma once

#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>
#include <Havok/Common/Base/Object/hkReferencedObject.h>

class hkpCdBody;
struct hkpCollisionInput;

class hkpConvexListFilter : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpConvexListFilter)

    enum ConvexListCollisionType {
        TREAT_CONVEX_LIST_AS_NORMAL,
        TREAT_CONVEX_LIST_AS_LIST,
        TREAT_CONVEX_LIST_AS_CONVEX,
    };

    virtual ConvexListCollisionType
    getConvexListCollisionType(const hkpCdBody& convexListBody, const hkpCdBody& otherBody,
                               const hkpCollisionInput& input) const = 0;

public:
    explicit hkpConvexListFilter(hkFinishLoadedObjectFlag flag) : hkReferencedObject(flag) {}

protected:
    hkpConvexListFilter() = default;
};
