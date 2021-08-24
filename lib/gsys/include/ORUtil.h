#pragma once

namespace sead {
class Heap;

namespace hostio {
class Node;
}
}  // namespace sead

namespace gsys::ORUtil {

enum Icon { _B = 0xB };

void setNodeMetaIcon(sead::hostio::Node*, Icon, sead::Heap*);

}  // namespace gsys::ORUtil
