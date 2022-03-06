#include "KingSystem/ActorSystem/actPhysicsConstraints.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"

namespace ksys::act {

PhysicsConstraints::PhysicsConstraints() = default;

PhysicsConstraints::~PhysicsConstraints() {
    finalize();
}

void PhysicsConstraints::finalize() {
    for (auto*& cs : mConstraints) {
        if (cs) {
            phys::Constraint::destroy(cs);
            cs = nullptr;
        }
    }
    mConstraints.freeBuffer();
    _10 = false;
    _11 = false;
}

}  // namespace ksys::act
