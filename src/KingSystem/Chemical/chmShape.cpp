#include "KingSystem/Chemical/chmShape.h"

namespace ksys::chm {

Shape::Shape()
    : agl::utl::IParameterIO("chmshp", 0), name({"untitled"}, "name", "名前", this),
      res_type_id({"----"}, "res_type_id", "マテリアルID", this),
      volume_occupancy(1.0, "volume_occupancy", "体積占有率", "Min=0, Max=1", this),
      element_occlusion(1.0, "element_occlusion", "エレメント遮蔽率", "Min=0, Max=1", this) {
    addObj(this, "res_shape");
}

Shape::~Shape() = default;

}  // namespace ksys::chm
