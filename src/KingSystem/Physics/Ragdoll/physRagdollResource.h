#pragma once

#include <resource/seadResource.h>

namespace ksys::phys {

class RagdollResource : public sead::DirectResource {
public:
    RagdollResource();
    ~RagdollResource() override;

    void doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) override;
};

}  // namespace ksys::phys
