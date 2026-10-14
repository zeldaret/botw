#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"

namespace ksys::phys {

class PolytopeShape;

class PolytopeRigidBody : public RigidBodyFromShape {
    SEAD_RTTI_OVERRIDE(PolytopeRigidBody, RigidBodyFromShape)
public:
    static PolytopeRigidBody* make(RigidBodyInstanceParam* param, sead::Heap* heap);

    PolytopeRigidBody(hkpRigidBody* hk_body, PolytopeShape* shape, ContactLayerType layer_type,
                      const sead::SafeString& name, bool set_flag_10, sead::Heap* heap);
    ~PolytopeRigidBody() override;

    bool setVertex(int vertex_idx, const sead::Vector3f& vertex);
    u16 getNumVertices() const;
    const sead::Vector3f& getVertex(int vertex_idx) const;

    void setMaterialMask(const MaterialMask& mask);
    const MaterialMask& getMaterialMask() const;

    float getVolume() override;
    void setVolume(float volume);

protected:
    Shape* getShape_() override;
    const Shape* getShape_() const override;
    u32 getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                          const sead::Vector3f& contact_point) override;

private:
    PolytopeShape* mShape{};
};

}  // namespace ksys::phys
