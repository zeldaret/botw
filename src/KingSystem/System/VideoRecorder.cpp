#include "KingSystem/System/VideoRecorder.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(VideoRecorder)

void VideoRecorder::postCalc() {
    if (!isCaptureEnabled())
        return;
    u32 framenum = mFrameNumber;
    sead::FixedSafeString<0x100> output;
    output.format("%s/%04d.tga", mFilename.cstr(), framenum);
    agl::utl::ScreenShotMgr::instance()->reserveCaptureWithDebugHeap(
        true, agl::TextureDataSerializerTGA::TGAFormat::_1, output, false);
    mFrameNumber++;
}

}  // namespace ksys