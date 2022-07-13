#include "KingSystem/System/VideoRecorder.h"

namespace ksys {
SEAD_SINGLETON_DISPOSER_IMPL(VideoRecorder)

void VideoRecorder::postCalc() {
    if (isCaptureEnabled()) {
        u32 framenum = frame_number;  // not sure why a new variable is created instead of using
                                      // frameNumber directly, might be a mistake?
        sead::FixedSafeString<0x100> output;
        output.format("%s/%04d.tga", filename.cstr(), framenum);
        agl::utl::ScreenShotMgr::instance()->reserveCaptureWithDebugHeap(1, 1, &output, 0);
        frame_number++;
    }
}
}  // namespace ksys