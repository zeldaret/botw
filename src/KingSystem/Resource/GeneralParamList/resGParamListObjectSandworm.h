#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectSandworm : public GParamListObject {
public:
    GParamListObjectSandworm();
    const char* getName() const override { return "Sandworm"; }

    agl::utl::Parameter<f32> mSandWidth;
    agl::utl::Parameter<f32> mSandLength;
    agl::utl::Parameter<f32> mSandHeight;
    agl::utl::Parameter<f32> mSandCombSpan;
    agl::utl::Parameter<f32> mSandCombHeight;
    agl::utl::Parameter<f32> mSnakeModelOffsetZ;
    agl::utl::Parameter<sead::SafeString> mSnakeBaseNode;
    agl::utl::Parameter<sead::SafeString> mSnakeNode1;
    agl::utl::Parameter<sead::SafeString> mSnakeNode2;
    agl::utl::Parameter<sead::SafeString> mSnakeNode3;
    agl::utl::Parameter<sead::SafeString> mSnakeNode4;
    agl::utl::Parameter<sead::SafeString> mSnakeNode5;
    agl::utl::Parameter<sead::SafeString> mSnakeNode6;
    agl::utl::Parameter<sead::SafeString> mSnakeNode7;
    agl::utl::Parameter<sead::SafeString> mSnakeNode8;
    agl::utl::Parameter<sead::SafeString> mSnakeNode9;
    agl::utl::Parameter<sead::SafeString> mSnakeNode10;
    agl::utl::Parameter<sead::SafeString> mSnakeNode11;
    agl::utl::Parameter<sead::SafeString> mSnakeNode12;
    agl::utl::Parameter<sead::Vector3f> mSnakeNodeRotOffset;
    agl::utl::Parameter<f32> mSnakeNodeChaseInterval;
    agl::utl::Parameter<f32> mShowLifeGageDist;
    agl::utl::Parameter<f32> mShowLifeGageOffset;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectSandworm, 0x388);

inline GParamListObjectSandworm::GParamListObjectSandworm() {
    auto* const obj = &mObj;

    mSandWidth.init(0.0, "SandWidth", "", obj);
    mSandLength.init(0.0, "SandLength", "", obj);
    mSandHeight.init(0.0, "SandHeight", "", obj);
    mSandCombSpan.init(0.0, "SandCombSpan", "", obj);
    mSandCombHeight.init(0.0, "SandCombHeight", "", obj);
    mSnakeModelOffsetZ.init(0.0, "SnakeModelOffsetZ", "", obj);
    mSnakeBaseNode.init("", "SnakeBaseNode", "", obj);
    mSnakeNode1.init("", "SnakeNode1", "", obj);
    mSnakeNode2.init("", "SnakeNode2", "", obj);
    mSnakeNode3.init("", "SnakeNode3", "", obj);
    mSnakeNode4.init("", "SnakeNode4", "", obj);
    mSnakeNode5.init("", "SnakeNode5", "", obj);
    mSnakeNode6.init("", "SnakeNode6", "", obj);
    mSnakeNode7.init("", "SnakeNode7", "", obj);
    mSnakeNode8.init("", "SnakeNode8", "", obj);
    mSnakeNode9.init("", "SnakeNode9", "", obj);
    mSnakeNode10.init("", "SnakeNode10", "", obj);
    mSnakeNode11.init("", "SnakeNode11", "", obj);
    mSnakeNode12.init("", "SnakeNode12", "", obj);
    mSnakeNodeRotOffset.init({0.0, 0.0, 0.0}, "SnakeNodeRotOffset", "", obj);
    mSnakeNodeChaseInterval.init(0.0, "SnakeNodeChaseInterval", "", obj);
    mShowLifeGageDist.init(150.0, "ShowLifeGageDist", "", obj);
    mShowLifeGageOffset.init(10.0, "ShowLifeGageOffset", "", obj);
}

}  // namespace ksys::res
