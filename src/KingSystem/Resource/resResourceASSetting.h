#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <agl/Utils/aglResParameter.h>
#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/Actor/resResourceASResourceExtension.h"
#include "KingSystem/Resource/resResource.h"

namespace ksys::res {

class ASSetting : public agl::utl::IParameterIO, public Resource {
    SEAD_RTTI_OVERRIDE(ASSetting, Resource)

public:
    struct BoneParam {
        agl::utl::ParameterObj mObj;
        agl::utl::Parameter<sead::SafeString> mBone;
        agl::utl::Parameter<float> mWeight;
    };
    KSYS_CHECK_SIZE_NX150(BoneParam, 0x78);

    class BoneParams : public ASParamParser {
        SEAD_RTTI_OVERRIDE(BoneParams, ASParamParser)
    public:
        BoneParams() : ASParamParser(Type::BlenderBone) {}
        ~BoneParams() override;
        bool parse(const ParseArgs& args) override;
        f32 getBoneWeight(const sead::SafeString& name) const;

        sead::Buffer<BoneParam> mBuffer;
    };

    struct BlenderBone {
        agl::utl::ParameterList mList;
        agl::utl::ParameterObj mNameParamObj;
        agl::utl::Parameter<sead::SafeString> mKeyName;
        BoneParams mBoneParams;
    };
    KSYS_CHECK_SIZE_NX150(BlenderBone, 0x108);

    ASSetting();
    ~ASSetting() override;

    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    sead::Buffer<BlenderBone>& getBlenderBones() { return mBlenderBones; }
    const sead::Buffer<BlenderBone>& getBlenderBones() const { return mBlenderBones; }

private:
    sead::Buffer<BlenderBone> mBlenderBones;
    agl::utl::ParameterList mBlenderBoneList;
};
KSYS_CHECK_SIZE_NX150(ASSetting, 0x260);

}  // namespace ksys::res
