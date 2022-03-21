/**
 * @file ResFile.h
 * @brief Resource file for models.
 */

#pragma once

#include <nn/gfx/api.h>
#include <nn/gfx/memory.h>
#include <nn/types.h>
#include <nn/util.h>

namespace nn {

namespace gfx {
template <typename T>
class TDevice;
}

namespace g3d {
class ResModel;
class ResMaterialAnim;
class ResShapeAnim;
class ResSceneAnim;
typedef void* TextureRef;

class ResFile : public nn::util::BinaryFileHeader {
public:
    static bool IsValid(void const* modelSrc);
    void Relocate();
    void Unrelocate();
    static nn::g3d::ResFile* ResCast(void*);
    s32 BindTexture(nn::g3d::TextureRef (*ref)(char const*, void*), void*);
    void ReleaseTexture();
    void
    Setup(nn::gfx::TDevice<nn::gfx::ApiVariation<nn::gfx::ApiType<4>, nn::gfx::ApiVersion<8>>>*);
    void
    Setup(nn::gfx::TDevice<nn::gfx::ApiVariation<nn::gfx::ApiType<4>, nn::gfx::ApiVersion<8>>>*,
          nn::gfx::TMemoryPool<nn::gfx::ApiVariation<nn::gfx::ApiType<4>, nn::gfx::ApiVersion<8>>>*,
          s64, u64);
    void
    Cleanup(nn::gfx::TDevice<nn::gfx::ApiVariation<nn::gfx::ApiType<4>, nn::gfx::ApiVersion<8>>>*);
    void Reset();

    u64 mFileNameLength;                  // _20
    nn::g3d::ResModel* mModels;           // _28
    u64 mModelDictOffset;                 // _30
    u64 mSkeleAnimOffset;                 // _38
    u64 mSkeleAnimDictOffset;             // _40
    nn::g3d::ResMaterialAnim* mMatAnims;  // _48
    u64 mMatAnimsDictOffset;              // _50
    u64 mBoneVisiOffset;                  // _58
    u64 mBoneVisiDictOffset;              // _60
    nn::g3d::ResShapeAnim* mShapeAnims;   // _68
    u64 mShapeAnimDictOffset;             // _70
    nn::g3d::ResSceneAnim* mSceneAnims;   // _78
    u64 mSceneAnimDictOffset;             // _80
    u64 mMemoryPool;                      // _88
    u64 mBufferSection;                   // _90
    u64 mEmbeddedFilesOffset;             // _98
    u64 mEmbeddedFilesDictOffset;         // _A0
    u64 mPadding;                         // _A8
    u64 mStrTableOffset;                  // _B0
    u32 mStrTableSize;                    // _B8
    u16 mModelCount;                      // _BC
    u16 mSkeleAnimCount;                  // _BE
    u16 mMatAnimCount;                    // _C0
    u16 mBoneAnimCount;                   // _C2
    u16 mShapeAnimCount;                  // _C4
    u16 mSceneAnimCount;                  // _C6
    u16 mExternalFileCount;               // _C8
    u8 mPad[0x6];                         // _CA
};
};  // namespace g3d
};  // namespace nn