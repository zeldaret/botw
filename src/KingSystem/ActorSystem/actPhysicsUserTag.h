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

    void m2(void* a) override;
    void m3(void* a, void* b, float c) override;
    void m4() override;
    void m5() override;
    const sead::SafeString& getName() const override;
    void m7() override;
    const sead::SafeString& getName2() const override;

private:
    Actor* mActor = nullptr;
    int _10 = -1;
    u16 _14 = 0;
};
KSYS_CHECK_SIZE_NX150(PhysicsUserTag, 0x18);

}  // namespace ksys::act
