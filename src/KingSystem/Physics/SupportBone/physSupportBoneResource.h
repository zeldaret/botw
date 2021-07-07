#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <resource/seadResource.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class SupportBoneResource : public sead::DirectResource, agl::utl::IParameterIO {
public:
    struct Bone : public agl::utl::ParameterObj {
        ~Bone();

        agl::utl::Parameter<sead::FixedSafeString<64>> name;
    };
    struct ConnectionLinear : public agl::utl::ParameterObj {
        agl::utl::Parameter<int> bone_attribute;  // TODO enum?
        agl::utl::Parameter<sead::Vector2f> slope_intercept;
    };
    struct ConnectionCurve : public agl::utl::ParameterObj {
        ~ConnectionCurve() = default;

        agl::utl::Parameter<int> bone_attribute;  // TODO enum?
        agl::utl::Parameter<bool> constant_in;
        agl::utl::Parameter<bool> constant_out;
        agl::utl::Parameter<sead::Vector4f> key0;
        agl::utl::Parameter<sead::Vector4f> key1;
        agl::utl::Parameter<sead::Vector4f> key2;
    };
    struct OutputSingle : public agl::utl::ParameterObj {
        agl::utl::Parameter<int> connection;
        agl::utl::Parameter<float> weight;
    };
    struct OutputDouble : public agl::utl::ParameterObj {
        ~OutputDouble() = default;

        agl::utl::Parameter<int> connection_0;
        agl::utl::Parameter<float> weight_0;
        agl::utl::Parameter<int> connection_1;
        agl::utl::Parameter<float> weight_1;
    };
    struct BaseBone : public agl::utl::ParameterObj {
        BaseBone();
        ~BaseBone();
        void postRead_() override;

        agl::utl::Parameter<int> bone;
        agl::utl::Parameter<sead::Vector3f> aim;
        agl::utl::Parameter<sead::Vector3f> up;
        agl::utl::Parameter<int> space;
        agl::utl::Parameter<sead::Quatf> base_rotate;
        agl::utl::Parameter<sead::Vector3f> base_translate;
        sead::Quatf reverse_rotate;
        sead::Vector3<float> side;
    };
    struct MainBone : public BaseBone {
        MainBone();
    };
    struct SupportBone : public BaseBone {
        SupportBone();
        ~SupportBone() = default;

        agl::utl::Parameter<int> bendH;
        agl::utl::Parameter<int> bendV;
        agl::utl::Parameter<int> roll;
        agl::utl::Parameter<int> translateX;
        agl::utl::Parameter<int> translateY;
        agl::utl::Parameter<int> translateZ;
    };

    SupportBoneResource();
    ~SupportBoneResource();

    void freeBuffers();
    int getSupportBoneIndexByName(const sead::SafeString& name);
    virtual void doCreate_(u8* data, u32 actualFileSize, sead::Heap* heap);
    bool init(agl::utl::ResParameterArchive archive, sead::Heap* heap);

    float getInterpolatedConnectionCurve(u32 index, float lookup);
    float somethingGetLinearConnection(u32 a2, float a3);

private:
    agl::utl::ParameterObj supportBoneHeader;
    agl::utl::ParameterList supportBoneData;
    // int gap_260;  // unknown purpose, 8 bytes
    agl::utl::Parameter<int> boneNum;
    agl::utl::ParameterList boneList;
    sead::Buffer<SupportBoneResource::Bone> boneBuffer;
    agl::utl::Parameter<int> connectionLinearNum;
    agl::utl::ParameterList connectionLinearList;
    sead::Buffer<SupportBoneResource::ConnectionLinear> connectionLinearBuffer;
    agl::utl::Parameter<int> connectionCurveNum;
    agl::utl::ParameterList connectionCurveList;
    sead::Buffer<SupportBoneResource::ConnectionCurve> connectionCurveBuffer;
    agl::utl::Parameter<int> outputSingleNum;
    agl::utl::ParameterList outputSingleList;
    sead::Buffer<SupportBoneResource::OutputSingle> outputSingleBuffer;
    agl::utl::Parameter<int> outputDoubleNum;
    agl::utl::ParameterList outputDoubleList;
    sead::Buffer<SupportBoneResource::OutputDouble> outputDoubleBuffer;
    agl::utl::Parameter<int> mainBoneNum;
    agl::utl::ParameterList mainBoneList;
    sead::Buffer<SupportBoneResource::MainBone> mainBoneBuffer;
    agl::utl::Parameter<int> supportBoneNum;
    agl::utl::ParameterList supportBoneList;
    sead::Buffer<SupportBoneResource::SupportBone> supportBoneBuffer;
};
KSYS_CHECK_SIZE_NX150(SupportBoneResource, 0x5B0);

}  // namespace ksys::phys