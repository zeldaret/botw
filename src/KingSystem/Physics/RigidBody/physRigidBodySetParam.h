#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>

namespace ksys::phys {

struct RigidBodyParam;

struct RigidBodySetParam : agl::utl::ParameterList {
    enum class Type {
        Invalid = 0,
        FromShapeType = 1,
        Other = 2,
    };

    RigidBodySetParam();
    ~RigidBodySetParam() override;
    RigidBodySetParam(const RigidBodySetParam&) = delete;
    auto operator=(const RigidBodySetParam&) = delete;

    bool parse(agl::utl::ResParameterList res_list, sead::Heap* heap);
    int getNumRigidBodies() const;

    Type type_val = Type::Invalid;
    agl::utl::ParameterObj obj;
    agl::utl::Parameter<sead::SafeString> set_name;
    agl::utl::Parameter<sead::SafeString> type;
    agl::utl::Parameter<int> num;
    agl::utl::Parameter<sead::SafeString> setup_file_path;
    sead::Buffer<RigidBodyParam> rigid_bodies;
};

}  // namespace ksys::phys
