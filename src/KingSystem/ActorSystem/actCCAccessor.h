#pragma once

namespace ksys::phys {
class CharacterController;
};

namespace ksys::act {

class Actor;

// todo: move?
enum class MotionType {
    Hover = 3,
};

class CCAccessor {
public:
    CCAccessor();
    ~CCAccessor();

    void changeMotionType(phys::CharacterController* cc, MotionType motion_type);
    void resetRigidBodyMotion(Actor* actor);
    void resetMotionType(phys::CharacterController* cc);
};

}  // namespace ksys::act
