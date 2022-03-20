#include "KingSystem/Physics/System/physRayCastForRequest.h"
#include "KingSystem/Physics/System/physRayCastRequestMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

RayCastForRequest::RayCastForRequest(RayCastRequestMgr* mgr)
    : RayCast(nullptr, GroundHit::HitAll), mMgr(mgr) {}

RayCastForRequest::~RayCastForRequest() = default;

RayCastForRequest* RayCastForRequest::allocRequest(SystemGroupHandler* group_handler,
                                                   GroundHit ground_hit) {
    return System::instance()->allocRayCastRequest(group_handler, ground_hit);
}

bool RayCastForRequest::submitRequest(ContactLayerType layer_type) {
    return mMgr->submitRequest(*this, layer_type);
}

bool RayCastForRequest::isRequestQueued() const {
    return mMgr->isRequestQueued(*this);
}

void RayCastForRequest::release() {
    mRigidBodyHitCallback = nullptr;
    mMgr->releaseRequest(*this);
}

bool RayCastForRequest::isRequestFinished() const {
    return mMgr->isRequestFinished(*this);
}

}  // namespace ksys::phys
