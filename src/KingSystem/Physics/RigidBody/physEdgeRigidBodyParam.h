#pragma once

#include <agl/utl/aglParameter.h>
#include <agl/utl/aglParameterList.h>
#include <agl/utl/aglParameterObj.h>
#include <container/seadBuffer.h>

namespace ksys::phys {

struct EdgeRigidBodyParam : agl::utl::ParameterObj {
    EdgeRigidBodyParam();
    ~EdgeRigidBodyParam() override;

    agl::utl::Parameter<sead::SafeString> set_name;
    agl::utl::Parameter<sead::SafeString> body_name;
    agl::utl::Parameter<sead::SafeString> edge_type;
};

struct EdgeRigidBodySetParam : agl::utl::ParameterList {
    EdgeRigidBodySetParam();
    ~EdgeRigidBodySetParam() override;
    EdgeRigidBodySetParam(const EdgeRigidBodySetParam&) = delete;
    auto operator=(const EdgeRigidBodySetParam&) = delete;

    void parse(int num, sead::Heap* heap);

    sead::Buffer<EdgeRigidBodyParam> edge_rigid_bodies;
};

}  // namespace ksys::phys
