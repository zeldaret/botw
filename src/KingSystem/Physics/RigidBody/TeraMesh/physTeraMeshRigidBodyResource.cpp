#include "KingSystem/Physics/RigidBody/TeraMesh/physTeraMeshRigidBodyResource.h"
#include <Havok/Common/Serialize/Util/hkNativePackfileUtils.h>
#include <Havok/Common/Serialize/Util/hkRootLevelContainer.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/RigidBody/TeraMesh/physTeraMeshRigidBody.h"
#include "KingSystem/Utils/Debug.h"

namespace ksys::phys {

TeraMeshRigidBodyResource::~TeraMeshRigidBodyResource() {
    delete mRigidBody;
    if (mHkpRigidBody)
        hkNativePackfileUtils::unloadInPlace(getRawData(), int(getRawSize()));
}

bool TeraMeshRigidBodyResource::parse_(u8* data, size_t size, sead::Heap* heap) {
    const char* error = nullptr;
    auto* container = static_cast<hkRootLevelContainer*>(
        hkNativePackfileUtils::loadInPlace(getRawData(), int(getRawSize()), nullptr, &error));
    if (!container) {
        util::PrintDebugFmt("failed to load TeraMeshRigidBody resource: %s", error);
    }

    mHkpRigidBody = container->findObject<hkpRigidBody>();
    mRigidBody = new (heap) TeraMeshRigidBody(mHkpRigidBody, heap);
    return mRigidBody != nullptr;
}

}  // namespace ksys::phys
