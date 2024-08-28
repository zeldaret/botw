#pragma once

#include <container/seadBuffer.h>
#include <utility/aglParameter.h>
#include <utility/aglParameterList.h>
#include <utility/aglParameterObj.h>

namespace ksys::phys {

struct ContactPointInfoParam : agl::utl::ParameterObj {
    ContactPointInfoParam();

    agl::utl::Parameter<sead::FixedSafeString<32>> name;
    agl::utl::Parameter<sead::FixedSafeString<32>> type;
    agl::utl::Parameter<int> num;
};

struct CollisionInfoParam : agl::utl::ParameterObj {
    CollisionInfoParam();

    agl::utl::Parameter<sead::FixedSafeString<32>> name;
    agl::utl::Parameter<sead::FixedSafeString<32>> type;
};

struct ContactInfoParam : agl::utl::ParameterList {
    ContactInfoParam();
    ~ContactInfoParam() override;
    ContactInfoParam(const ContactInfoParam&) = delete;
    auto operator=(const ContactInfoParam&) = delete;

    bool parse(const agl::utl::ResParameterList& res_list, sead::Heap* heap);

    sead::Buffer<ContactPointInfoParam> contact_point_info;
    sead::Buffer<CollisionInfoParam> collision_info;
    agl::utl::ParameterObj obj;
    agl::utl::Parameter<int> contact_point_info_num;
    agl::utl::Parameter<int> collision_info_num;
};

}  // namespace ksys::phys
