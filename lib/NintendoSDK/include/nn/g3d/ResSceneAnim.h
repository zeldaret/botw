/**
 * @file ResSceneAnim.h
 * @brief Resource file for scene animations.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace g3d {
class ResLightAnim;
class ResFogAnim;
struct BindFuncTable;

class ResSceneAnim {
public:
    s32 Bind(nn::g3d::BindFuncTable const&);
    void Release();
    void Reset();

    char mMagic[4];                      // _0
    s32 mBlockOffset;                    // _4
    u64 mBlockSize;                      // _8
    u64 mNameOffset;                     // _10
    u64 mPathOffset;                     // _18
    u64 mCameraAnimOffset;               // _20
    u64 mCameraAnimDictOffset;           // _28
    nn::g3d::ResLightAnim* mLightAnims;  // _30
    u64 mLightAnimDictOffset;            // _38
    nn::g3d::ResFogAnim* mFogAnims;      // _40
    u64 mFogAnimDictOffset;              // _48
    u64 mUserDataOffset;                 // _50
    u64 mUserDataDictOffset;             // _58
    u16 mUserDataCount;                  // _60
    u16 mCameraAnimCount;                // _62
    u16 mLightAnimCount;                 // _64
    u16 mFogAnimCount;                   // _66
};
};  // namespace g3d
};  // namespace nn