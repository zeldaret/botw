#pragma once

#include <filedevice/seadMainFileDevice.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class OffsetRead {
public:
    OffsetRead() { resetOffsetRead(); }
    virtual ~OffsetRead() = default;

    void setReadOffset(u32 offset) { mOffsetReadOffset = offset; }
    void setFileDevice(sead::FileDevice* device) { mOffsetReadFileDevice = device; }

    void resetOffsetRead() {
        mOffsetReadOffset = 0;
        mOffsetReadFileDevice = nullptr;
    }

protected:
    u32 mOffsetReadOffset;
    sead::FileDevice* mOffsetReadFileDevice;
};
KSYS_CHECK_SIZE_NX150(OffsetRead, 0x18);

class OffsetReadFileDevice : public sead::MainFileDevice, public OffsetRead {
    SEAD_RTTI_OVERRIDE(OffsetReadFileDevice, sead::MainFileDevice)
public:
    explicit OffsetReadFileDevice(sead::Heap* heap);
    ~OffsetReadFileDevice() override = default;

    void setReadOffset(u32 offset) { OffsetRead::setReadOffset(offset); }
    void setFileDevice(sead::FileDevice* device);

protected:
    u8* doLoad_(LoadArg& arg) override;
};
KSYS_CHECK_SIZE_NX150(OffsetReadFileDevice, 0xa0);

}  // namespace ksys::res
