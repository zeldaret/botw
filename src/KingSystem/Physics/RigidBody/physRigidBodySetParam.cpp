#include "KingSystem/Physics/RigidBody/physRigidBodySetParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace ksys::phys {

RigidBodySetParam::RigidBodySetParam()
    : set_name(sead::SafeString::cEmptyString, "set_name", &obj),
      type(sead::SafeString::cEmptyString, "type", &obj), num(1, "num", &obj),
      setup_file_path(sead::SafeString::cEmptyString, "setup_file_path", &obj) {}

RigidBodySetParam::~RigidBodySetParam() {
    rigid_bodies.freeBuffer();
}

bool RigidBodySetParam::parse(agl::utl::ResParameterList res_list, sead::Heap* heap) {
    if (!res_list)
        return false;

    obj.applyResParameterObj(res_list.getResParameterObj(0));

    if (*type == "from_shape_type")
        type_val = Type::FromShapeType;
    else
        type_val = Type::Other;

    const int num_bodies = *num;
    if (num_bodies == 0 || res_list.getResParameterListNum() != num_bodies)
        return false;

    rigid_bodies.allocBufferAssert(num_bodies, heap);
    for (int i = 0; i < num_bodies; ++i) {
        rigid_bodies[i].parse(res_list.getResParameterList(i), heap);
    }

    return true;
}

int RigidBodySetParam::getNumRigidBodies() const {
    return *num;
}

}  // namespace ksys::phys
