#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace ksys::phys {

class LayerMaskBuilder;
class RigidBody;
class QueryContactPointInfo;

class ClosestPointQuery {
    SEAD_RTTI_BASE(ClosestPointQuery)
public:
    ClosestPointQuery(RigidBody* body, QueryContactPointInfo* contact_point_info);
    virtual ~ClosestPointQuery();

    RigidBody* getBody() const { return mBody; }
    QueryContactPointInfo* getContactPointInfo() const { return mContactPointInfo; }

    void setLayerMasks(const LayerMaskBuilder& builder);
    void setLayerMasksAndBodyCollisionFilterInfo(const LayerMaskBuilder& builder);

    // 0x0000007100fb0850
    bool execute(bool unk);
    bool isSuccess() const;

protected:
    void reset();

    RigidBody* mBody{};
    QueryContactPointInfo* mContactPointInfo{};
    u32 _18{};
    bool mIsSuccess = false;
    sead::Matrix34f mMtx = sead::Matrix34f::ident;
};

}  // namespace ksys::phys
