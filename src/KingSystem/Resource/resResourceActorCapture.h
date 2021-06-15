#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

class ActorCapture : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(ActorCapture, Resource)
public:
    struct ActorCaptureConstants {
        // NON_MATCHING: equivalent but reordered
        ActorCaptureConstants() {
            camera_position = {0.0, 2.0, 5.0};
            camera_direction = {0.0, 2.0, 0.0};
            light_direction = {0.5720610022544861, -0.7071070075035095, -0.41562700271606445};
            actor_position = sead::Vector3f::zero;
            actor_rotation = sead::Vector3f::zero;
        }
        sead::Vector3f camera_position;
        sead::Vector3f camera_direction;
        sead::Vector3f light_direction;
        sead::Vector3f actor_position;
        sead::Vector3f actor_rotation;
    };

    struct CameraInfo : agl::utl::ParameterObj {
        agl::utl::Parameter<sead::Vector3f> position;
        agl::utl::Parameter<sead::Vector3f> direction;
        agl::utl::Parameter<f32> fov;
        agl::utl::Parameter<f32> tilt;
    };

    struct ActorInfo : agl::utl::ParameterObj {
        agl::utl::Parameter<sead::Vector3f> position;
        agl::utl::Parameter<sead::Vector3f> rotation;
        agl::utl::Parameter<sead::FixedSafeString<32>> as_name;
        agl::utl::Parameter<bool> apply_skel_anim;
        agl::utl::Parameter<f32> frame;
        agl::utl::Parameter<bool> bounding_adjustment;
        agl::utl::Parameter<bool> force_idle;
        agl::utl::Parameter<bool> disable_cloth;
    };

    struct LightInfo : agl::utl::ParameterObj {
        agl::utl::Parameter<sead::Vector3f> direction;
    };

    ActorCapture();

    void doCreate_(u8*, u32, sead::Heap*) override {}
    bool needsParse() const override { return true; }
    bool ParamIO_m0(char* data) override { return true; }

    void reset();

    static const ActorCaptureConstants& getConstants();

    CameraInfo mCameraInfoObj;
    ActorInfo mActorInfoObj;
    LightInfo mLightInfoObj;

private:
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
};
KSYS_CHECK_SIZE_NX150(ActorCapture, 0x538);

}  // namespace ksys::res
