#pragma once

#include <nn/types.h>

namespace nn {
namespace g3d {
class ResFogAnim {
public:
    char mMagic[4];           // _0
    u16 mFlags;               // _4
    u16 mPad;                 // _6
    s32 mNumFrames;           // _8
    u8 mNumCurves;            // _C
    u8 mIdxDistanceAttnFunc;  // _D
    u16 mNumUserData;         // _E
    u32 mSizeBaked;           // _10
    u64 mNameOffset;          // _14
    u64 mFuncNameOffset;      // _1C
};
};  // namespace g3d
};  // namespace nn