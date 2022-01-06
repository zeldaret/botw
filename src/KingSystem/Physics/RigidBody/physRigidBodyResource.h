#pragma once

#include <resource/seadResource.h>

namespace ksys::phys {

class RigidBodyResource : public sead::DirectResource {
    SEAD_RTTI_OVERRIDE(RigidBodyResource, sead::DirectResource)

public:
    RigidBodyResource();
    ~RigidBodyResource() override;

    void doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) override;
};

}  // namespace ksys::phys
