#pragma once

#include "KingSystem/Resource/resResource.h"

class hkpRigidBody;

namespace ksys::phys {

class TeraMeshRigidBody;

class TeraMeshRigidBodyResource : public res::Resource {
    SEAD_RTTI_OVERRIDE(TeraMeshRigidBodyResource, res::Resource)

public:
    TeraMeshRigidBodyResource() = default;
    ~TeraMeshRigidBodyResource() override;

    hkpRigidBody* getHkpRigidBody() const { return mHkpRigidBody; }
    TeraMeshRigidBody* getRigidBody() const { return mRigidBody; }

    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

private:
    hkpRigidBody* mHkpRigidBody = nullptr;
    TeraMeshRigidBody* mRigidBody = nullptr;
};

}  // namespace ksys::phys
