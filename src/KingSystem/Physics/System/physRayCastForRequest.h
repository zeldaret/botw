#pragma once

#include <container/seadTList.h>
#include "KingSystem/Physics/System/physRayCast.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class RayCastRequestMgr;

/// A RayCast that is used by RayCastRequestMgr to process raycast requests.
class RayCastForRequest : public RayCast {
    SEAD_RTTI_OVERRIDE(RayCastForRequest, RayCast)
public:
    static RayCastForRequest* allocRequest(SystemGroupHandler* group_handler = nullptr,
                                           GroundHit ground_hit = GroundHit::HitAll);

    explicit RayCastForRequest(RayCastRequestMgr* mgr);
    ~RayCastForRequest() override;

    bool submitRequest(ContactLayerType layer_type);
    bool isRequestQueued() const;
    bool isRequestFinished() const;

    /// This must be called after you're finished using this RayCast.
    void release();

private:
    friend class RayCastRequestMgr;

    RayCastRequestMgr* mMgr{};
    sead::TListNode<RayCastForRequest*> mListNode{this};
    ContactLayerType mRequestContactLayerType = ContactLayerType::Entity;
};

}  // namespace ksys::phys
