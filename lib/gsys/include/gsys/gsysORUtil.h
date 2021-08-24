#pragma once

namespace sead {
class Heap;

namespace hostio {
class Node;
}
}  // namespace sead

namespace gsys::ORUtil {

enum class Icon {
    _b = 0xB,
};

void setNodeMetaIcon(sead::hostio::Node* node, Icon icon, sead::Heap* heap);

}  // namespace gsys::ORUtil
