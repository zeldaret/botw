#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>

namespace ksys::snd {

enum class AudioChannelType {
    Mono = 1,
    Stereo = 2,
    _5_1ch = 6,
    Other = -1  // TODO: does Other have a definite value?
};

class FxMgr {
public:
    // Destructor is virtual to implicitly establish a vtable pointer at offset 0x00.
    virtual ~FxMgr();

    // Invokes the audio system effect when entering a slow motion state.
    void setSlowTime(bool is_4);

    // Deactivates the active slow motion audio filter.
    void endSlowTime();

    // Pad from the end of the vtable pointer (0x08) to the state variable (0x30).
    u8 _8[0x28];
    // Variable representing the state of the audio effect controller.
    u32 mState;
};

// FIXME: incomplete
struct SoundMgr {
    SEAD_SINGLETON_DISPOSER(SoundMgr)

    virtual ~SoundMgr();

public:
    // Padding spanning from the end of the disposer block (0x28) to the FxMgr pointer (0x90).
    u8 _28[0x90 - 0x28];
    // Pointer to the Sound Effects Manager, aligned precisely at offset 0x90.
    FxMgr* mFxMgr;
    // Remaining bytes of the padding array to preserve the original struct layout size.
    u8 _98[0x248 - (0x90 - 0x28) - 8];
    AudioChannelType mAudioChannelType;
};

}  // namespace ksys::snd
