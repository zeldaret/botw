#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <utility/aglParameter.h>
#include <utility/aglParameterObj.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

class ActorCapture : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(ActorCapture, Resource)
public:
    struct ActorCaptureConstants {
#ifdef MATCHING_HACK_NX_CLANG
        ActorCaptureConstants() {
            register const sead::Vector3f* zero_ptr asm("x8") = &sead::Vector3f::zero;
            asm(
                "orr     x10, xzr, #0x4000000000000000\n"
                "mov     w11, #0x40a00000\n"
                "stp     x10, x11, [%0]\n"
                "ldr     w10, [%1, #0x8]\n"
                "str     w10, [%0, #0x2c]\n"
                "ldr     x10, [%1]\n"
                "stur    x10, [%0, #0x24]\n"
                "ldr     w10, [%1, #0x8]\n"
                "ldr     x8, [%1]\n"
                "str     x8, [%0, #0x30]\n"
                "mov     x8, #-0x40cb000000000000\n"
                "movk    x8, #0x4f7, lsl #0x20\n"
                "movk    x8, #0x3f12, lsl #0x10\n"
                "str     w10, [%0, #0x38]\n"
                "orr     w10, wzr, #0x40000000\n"
                "movk    x8, #0x7297\n"
                "stp     x10, x8, [%0, #0x10]\n"
                "mov     w8, #-0x412c0000\n"
                "movk    w8, #0xcd10\n"
                "str     w8, [%0, #0x20]\n"
                :: "r"(this), "r"(zero_ptr)
                : "x8", "x10", "x11", "memory"
            );
        }
#else
        ActorCaptureConstants()
            : camera_position{0.0, 2.0, 5.0},
              camera_direction{0.0, 2.0, 0.0},
              light_direction{0.5720610022544861, -0.7071070075035095, -0.41562700271606445},
              actor_position(sead::Vector3f::zero),
              actor_rotation(sead::Vector3f::zero) {}
#endif
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
