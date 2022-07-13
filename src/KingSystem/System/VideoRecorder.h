#pragma once

#include <basis/seadNew.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class VideoRecorder {
    SEAD_SINGLETON_DISPOSER(VideoRecorder)
    VideoRecorder() = default;
    virtual ~VideoRecorder();

public:
    void postCalc();
    bool isCaptureEnabled() const { return capture_enabled; }
    int getFrameNumber() const { return frame_number; }
    sead::FixedSafeString<0x100> getFileName() const { return filename; }

private:
    bool capture_enabled = false;  // 0x28
    bool _29 = true;       // 0x29, this gets set to true but isn't used elsewhere, no idea why
    u32 frame_number = 0;  // 0x2C
    sead::FixedSafeString<0x100> filename;  // 0x30
};

KSYS_CHECK_SIZE_NX150(VideoRecorder, 0x148);
}  // namespace ksys

namespace agl::utl {  // temp because this namespace doesn't exist in the sead decomp yet, remove
                      // this once added

class ScreenShotMgr {
    SEAD_SINGLETON_DISPOSER(ScreenShotMgr)
    ScreenShotMgr() = default;
    virtual ~ScreenShotMgr();

public:
    u64 reserveCaptureWithDebugHeap(bool somebool, u64 someint, const sead::SafeString*,
                                    bool secondbool);
};
}  // namespace agl::utl