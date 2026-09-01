#include "gsys/gsysApplicationPackageInfo.h"

#include <filedevice/seadPath.h>

namespace gsys {

namespace {  // TODO: better names?
const sead::SafeString cNamespaceKey = "gsys";
const sead::SafeString cGmsconfKey = "gmsconf";
const sead::SafeString cPtlconfKey = "ptlconf";
const sead::SafeString cGapkgInfoKey = "gapkginfo";
const sead::SafeString cGapkgListKey = "gapkglist";
const sead::SafeString cPackageNameKey = "package_name";
const sead::SafeString cShaderKey = "shader";
const sead::SafeString cShaderNumKey = "shader_num";
const sead::SafeString cShaderBinaryKey = "g3d_shader_binary";
const sead::SafeString cShaderTextKey = "g3d_shader_text";
const sead::SafeString cBfresKey = "bfres";
const sead::SafeString cBfresNumKey = "bfres_num";
const sead::SafeString cAglSharcKey = "agl_sharc";
const sead::SafeString cAglSharcNumKey = "agl_sharc_num";
const sead::SafeString cSharcKey = "sharc";
const sead::SafeString cSharcbKey = "sharcb";
const sead::SafeString cFileKey = "file";

const bool cHasGapkgInfo =
    true;  // TODO: do these booleans actually exist? There isn't any proof that they existing
           // because initializeFromArchive_ doesn't need if, just {}
const bool cHasGapkgList = true;
const bool cHasPtclConf = true;
const bool cHasBgmsConf = true;
}  // namespace

ApplicationPackageInfo::ApplicationPackageInfo()
    : mGapkgInfo(cGapkgInfoKey, 0),
      mPackageName(cPackageNameKey, cPackageNameKey, cPackageNameKey, &mParameterObj),
      mShaderNum(0, cShaderNumKey, cShaderNumKey, &mParameterObj),
      mBfresNum(0, cBfresNumKey, cBfresNumKey, &mParameterObj),
      mAglSharcNum(0, cAglSharcNumKey, cAglSharcNumKey, &mParameterObj),
      mGapkgList(cGapkgListKey, 0) {
    mGapkgInfo.addObj(&mParameterObj, "gsys_app_package_info");
}

ApplicationPackageInfo::~ApplicationPackageInfo() {  // mBfresInfos and mAglShadersInfo aren't
                                                     // freed, maybe it's a bug in gsys
    mShaderFilesNamesInfo.freeBuffer();
}

void ApplicationPackageInfo::initializeFromArchive_(sead::ArchiveRes* res, sead::Heap* heap) {
    if (cHasGapkgInfo) {  // The `if` itself isn't required for a full match — only the enclosing
                          // braces are, since they're what destroys these locals at the end of the
                          // block. A bare `{ }` with no `if` seems unlikely in the original source
                          // though, so this is probably an `if` on a compile-time-constant boolean.
        sead::FixedSafeString<64> gapkginfo_filename;
        getGapkginfoFilename(&gapkginfo_filename);
        const void* gapkginfo_file = res->getFile(gapkginfo_filename);
        mGapkgInfo.applyResParameterArchive(agl::utl::ResParameterArchive(gapkginfo_file));
    }

    const s32 shader_num = *mShaderNum;
    if (shader_num > 0)
        mShaderFilesNamesInfo.allocBufferAssert(shader_num, heap);
    for (s32 i = 0; i < shader_num; i++)
        mGapkgList.addObj(&mShaderFilesNamesInfo[i],
                          sead::FormatFixedSafeString<64>("%s_%02d", cShaderKey.cstr(), i));

    const s32 bfres_num = *mBfresNum;
    if (bfres_num > 0)
        mBfresInfos.allocBufferAssert(bfres_num, heap);
    for (s32 i = 0; i < bfres_num; i++)
        mGapkgList.addObj(&mBfresInfos[i],
                          sead::FormatFixedSafeString<64>("%s_%02d", cBfresKey.cstr(), i));

    const s32 agl_sharc_num = *mAglSharcNum;
    if (agl_sharc_num > 0)
        mAglShadersInfo.allocBufferAssert(agl_sharc_num, heap);
    for (s32 i = 0; i < agl_sharc_num; i++)
        mGapkgList.addObj(&mAglShadersInfo[i],
                          sead::FormatFixedSafeString<64>("%s_%02d", cAglSharcKey.cstr(), i));

    if (cHasGapkgList) {  // The `if` itself isn't required for a full match — only the enclosing
                          // braces are, since they're what destroys these locals at the end of the
                          // block. A bare `{ }` with no `if` seems unlikely in the original source
                          // though, so this is probably an `if` on a compile-time-constant boolean.
        sead::FixedSafeString<64> gapkglist_filename;
        getGapkglistFilename(&gapkglist_filename);
        const void* gapkglist_file = res->getFile(gapkglist_filename);
        mGapkgList.applyResParameterArchive(agl::utl::ResParameterArchive(gapkglist_file));
    }
}

void ApplicationPackageInfo::getBinaryFilename(sead::BufferedSafeString* filename,
                                               sead::SafeString& path) {
    sead::FixedSafeString<16> ext;
    sead::Path::getExt(&ext, path);
    sead::Path::getFileName(filename, path);
    filename->removeSuffix(ext);
    filename->appendWithFormat("b%s", ext.cstr());
}

void ApplicationPackageInfo::getGmsconfFilename(sead::BufferedSafeString* filename) {
    sead::FixedSafeString<64> base_filename;
    base_filename.format("%s.%s", cNamespaceKey.cstr(), cGmsconfKey.cstr());
    getBinaryFilename(filename, base_filename);
}

void ApplicationPackageInfo::getPtlconfFilename(sead::BufferedSafeString* filename) {
    sead::FixedSafeString<64> base_filename;
    base_filename.format("%s.%s", cNamespaceKey.cstr(), cPtlconfKey.cstr());
    getBinaryFilename(filename, base_filename);
}

void ApplicationPackageInfo::getGapkginfoFilename(sead::BufferedSafeString* filename) {
    sead::FixedSafeString<64> base_filename;
    base_filename.format("%s.%s", cNamespaceKey.cstr(), cGapkgInfoKey.cstr());
    getBinaryFilename(filename, base_filename);
}

void ApplicationPackageInfo::getGapkglistFilename(sead::BufferedSafeString* filename) {
    sead::FixedSafeString<64> base_filename;
    base_filename.format("%s.%s", cNamespaceKey.cstr(), cGapkgListKey.cstr());
    getBinaryFilename(filename, base_filename);
}

ApplicationPackageInfo::ShaderFileNameInfo::ShaderFileNameInfo()
    : mShaderBinary(sead::SafeString::cEmptyString, cShaderBinaryKey, cShaderBinaryKey, this),
      mShaderText(sead::SafeString::cEmptyString, cShaderTextKey, cShaderTextKey, this) {}
ApplicationPackageInfo::ShaderFileNameInfo::~ShaderFileNameInfo() = default;

ApplicationPackageInfo::BfresInfo::BfresInfo()
    : mFile(sead::SafeString::cEmptyString, cFileKey, cFileKey, this) {}
ApplicationPackageInfo::BfresInfo::~BfresInfo() = default;

ApplicationPackageInfo::AglShaderInfo::AglShaderInfo()
    : mSharc(sead::SafeString::cEmptyString, cSharcKey, cSharcKey, this),
      mSharcb(sead::SafeString::cEmptyString, cSharcbKey, cSharcbKey, this) {}
ApplicationPackageInfo::AglShaderInfo::~AglShaderInfo() = default;

}  // namespace gsys