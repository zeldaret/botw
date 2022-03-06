#include "KingSystem/Physics/Constraint//physConstraint.h"

namespace ksys::phys {

void Constraint::destroy(Constraint* instance) {
    delete instance;
}

}  // namespace ksys::phys
