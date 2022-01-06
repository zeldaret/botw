#pragma once

#include <prim/seadSafeString.h>
#include <resource/seadResource.h>

namespace ksys::phys {

class ClothResource : public sead::DirectResource {
public:
    ClothResource();
    ~ClothResource() override;

    void doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) override;

private:
    void* _20{};
    int _28{};
    void* _30{};
    int _38{};
    void* _40{};
    u8 _48{};
    sead::FixedSafeString<128> _50;
};

}  // namespace ksys::phys
