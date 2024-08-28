#pragma once

#include <container/seadBuffer.h>
#include <utility/aglParameter.h>
#include <utility/aglParameterList.h>
#include <utility/aglParameterObj.h>

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
