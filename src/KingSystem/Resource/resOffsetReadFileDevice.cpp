#include "KingSystem/Resource/resOffsetReadFileDevice.h"
#include <heap/seadHeapMgr.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

OffsetReadFileDevice::OffsetReadFileDevice(sead::Heap* heap) : sead::MainFileDevice(heap) {
    resetOffsetRead();
}

void OffsetReadFileDevice::setFileDevice(sead::FileDevice* device) {
    OffsetRead::setFileDevice(device);
}

/// This is a modified version of `sead::FileDevice::doLoad_`.
u8* OffsetReadFileDevice::doLoad_(sead::FileDevice::LoadArg& arg) {
    if (arg.buffer && arg.buffer_size == 0) {
        stubbedLogFunction();
        return nullptr;
    }

    sead::FileDevice* device = mOffsetReadFileDevice;
    if (!device)
        device = this;

    sead::FileHandle handle;
    if (!device->tryOpen(&handle, arg.path, FileDevice::cFileOpenFlag_ReadOnly, arg.div_size))
        return nullptr;

    u32 bytesToRead = arg.buffer_size;
    if (!arg.buffer || arg.check_read_entire_file) {
        u32 fileSize = 0;
        if (!device->tryGetFileSize(&fileSize, &handle))
            return nullptr;

        if (fileSize == 0) {
            stubbedLogFunction();
            return nullptr;
        }

        if (bytesToRead != 0) {
            if (bytesToRead < fileSize) {
                stubbedLogFunction();
                return nullptr;
            }
        } else {
            bytesToRead = mOffsetReadOffset +
                          sead::Mathi::roundUpPow2(fileSize, FileDevice::cBufferMinAlignment);
        }
    }

    u8* buf = arg.buffer;
    bool allocated = false;

    if (buf == nullptr) {
        const s32 sign = (arg.alignment < 0) ? -1 : 1;
        s32 alignment = sead::Mathi::abs(arg.alignment);
        alignment = sign * ((alignment < cBufferMinAlignment) ? cBufferMinAlignment : alignment);

        sead::Heap* heap = arg.heap;
        if (!heap)
            heap = sead::HeapMgr::instance()->getCurrentHeap();

        void* raw_buf = heap->tryAlloc(bytesToRead, alignment);
        if (!raw_buf)
            return nullptr;

        buf = new (raw_buf) u8[bytesToRead];
        allocated = true;
    }

    u32 bytesRead = 0;
    if (!device->tryRead(&bytesRead, &handle, buf + mOffsetReadOffset,
                         bytesToRead - mOffsetReadOffset)) {
        if (allocated)
            delete[] buf;
        return nullptr;
    }

    if (!device->tryClose(&handle)) {
        if (allocated)
            delete[] buf;
        return nullptr;
    }

    arg.read_size = bytesRead;
    arg.roundup_size = bytesToRead;
    arg.need_unload = allocated;

    return buf;
}

}  // namespace ksys::res
