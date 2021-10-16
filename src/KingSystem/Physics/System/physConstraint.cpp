#include "KingSystem/Physics/System/physConstraint.h"

namespace ksys::phys {

void Constraint::destroy(Constraint* instance) {
    if (instance)
        delete instance;
}

}  // namespace ksys::phys
