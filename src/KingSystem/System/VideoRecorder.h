#pragma once

#include <agl/utl/aglScreenShotMgr.h>
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
    bool isCaptureEnabled() const { return mCaptureEnabled; }
    u32 getFrameNumber() const { return mFrameNumber; }
    const sead::SafeString& getFileName() const { return mFilename; }

private:
    bool mCaptureEnabled = false;
    bool _29 = true;
    u32 mFrameNumber = 0;
    sead::FixedSafeString<0x100> mFilename;
};

KSYS_CHECK_SIZE_NX150(VideoRecorder, 0x148);

}  // namespace ksys