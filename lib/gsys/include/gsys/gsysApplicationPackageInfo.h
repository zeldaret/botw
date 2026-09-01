#pragma once

#include <utility/aglParameter.h>
#include <utility/aglParameterIO.h>
#include <utility/aglParameterObj.h>

#include <container/seadBuffer.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>
#include <resource/seadArchiveRes.h>

namespace gsys {

class ApplicationPackageInfo {
public:
    ApplicationPackageInfo();
    virtual ~ApplicationPackageInfo();

    void initializeFromArchive_(sead::ArchiveRes* res, sead::Heap* heap);

    static void getGmsconfFilename(sead::BufferedSafeString* filename);
    static void getPtlconfFilename(sead::BufferedSafeString* filename);
    static void getGapkginfoFilename(sead::BufferedSafeString* filename);
    static void getGapkglistFilename(sead::BufferedSafeString* filename);

private:
    class ShaderFileNameInfo : public agl::utl::IParameterObj {
    public:
        ShaderFileNameInfo();
        ~ShaderFileNameInfo() override;

    private:
        agl::utl::Parameter<sead::FixedSafeString<64>> mShaderBinary;
        agl::utl::Parameter<sead::FixedSafeString<64>> mShaderText;
    };

    class BfresInfo : public agl::utl::IParameterObj {
    public:
        BfresInfo();
        ~BfresInfo() override;

    private:
        agl::utl::Parameter<sead::FixedSafeString<64>> mFile;
    };

    class AglShaderInfo : public agl::utl::IParameterObj {
    public:
        AglShaderInfo();
        ~AglShaderInfo() override;

    private:
        agl::utl::Parameter<sead::FixedSafeString<64>> mSharc;
        agl::utl::Parameter<sead::FixedSafeString<64>> mSharcb;
    };

    agl::utl::IParameterIO mGapkgInfo;
    agl::utl::IParameterObj mParameterObj;
    agl::utl::Parameter<sead::FixedSafeString<64>> mPackageName;
    agl::utl::Parameter<s32> mShaderNum;
    agl::utl::Parameter<s32> mBfresNum;
    agl::utl::Parameter<s32> mAglSharcNum;
    agl::utl::IParameterIO mGapkgList;
    sead::Buffer<ShaderFileNameInfo> mShaderFilesNamesInfo;
    sead::Buffer<BfresInfo> mBfresInfos;
    sead::Buffer<AglShaderInfo> mAglShadersInfo;

    static void getBinaryFilename(sead::BufferedSafeString* filename, sead::SafeString& path);
};

}  // namespace gsys