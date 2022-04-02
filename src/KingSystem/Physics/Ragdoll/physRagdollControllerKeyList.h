#pragma once

#include <agl/utl/aglParameter.h>
#include <agl/utl/aglParameterObj.h>
#include <container/seadBuffer.h>

#include "KingSystem/Resource/resResource.h"

namespace ksys::phys {

class RagdollControllerKeyList : public ksys::res::Resource {
    SEAD_RTTI_OVERRIDE(RagdollControllerKeyList, ksys::res::Resource)

    struct RagdollControllerKey : public agl::utl::ParameterObj {
        RagdollControllerKey();

        agl::utl::Parameter<sead::SafeString> key;
        agl::utl::Parameter<float> hierarchy_gain;
        agl::utl::Parameter<float> velocity_damping;
        agl::utl::Parameter<float> acceleration_gain;
        agl::utl::Parameter<float> velocity_gain;
        agl::utl::Parameter<float> position_gain;
        agl::utl::Parameter<float> position_max_linear_velocity;
        agl::utl::Parameter<float> position_max_angular_velocity;
        agl::utl::Parameter<float> snap_gain;
        agl::utl::Parameter<float> snap_max_linear_velocity;
        agl::utl::Parameter<float> snap_max_angular_velocity;
        agl::utl::Parameter<float> snap_max_linear_distance;
        agl::utl::Parameter<float> snap_max_angular_distance;
    };
    KSYS_CHECK_SIZE_NX150(RagdollControllerKey, 0x1D8);

public:
    RagdollControllerKeyList();
    ~RagdollControllerKeyList();

    RagdollControllerKey* getControllerKeyByKey(const sead::SafeString& key);

private:
    bool parse_(u8* data, size_t actualFileSize, sead::Heap* heap) override;
    bool needsParse() const override { return true; }

    sead::Buffer<RagdollControllerKey> buffer;
};

}  // namespace ksys::phys
