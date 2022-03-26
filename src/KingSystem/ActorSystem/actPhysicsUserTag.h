#pragma once

#include "KingSystem/Physics/System/physUserTag.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;
class ActorLinkConstDataAccess;

class PhysicsUserTag : public phys::UserTag {
    SEAD_RTTI_OVERRIDE(PhysicsUserTag, phys::UserTag)

public:
    explicit PhysicsUserTag(Actor* actor);
    ~PhysicsUserTag() override;

    Actor* getActor(ActorLinkConstDataAccess* accessor, Actor* other_actor) const;
    bool acquireActor(ActorLinkConstDataAccess* accessor) const;

    Actor* getActor() const { return mActor; }

    void onMaxPositionExceeded(phys::RigidBody* body) override;
    void onImpulse(phys::RigidBody* body_a, phys::RigidBody* body_b, float impulse_a) override;
    void onBodyShapeChanged(phys::RigidBody* body) override;
    void m5() override;
    const sead::SafeString& getName() const override;
    void m7(phys::RigidBody* rigid_body, int a) override;
    const sead::SafeString& getName(phys::RigidBody* rigid_body) const override;

private:
    Actor* mActor = nullptr;
    int _10 = -1;
    u16 _14 = 0;
};
KSYS_CHECK_SIZE_NX150(PhysicsUserTag, 0x18);

}  // namespace ksys::act
