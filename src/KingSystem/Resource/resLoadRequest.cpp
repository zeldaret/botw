#include "KingSystem/Resource/resLoadRequest.h"

namespace ksys::res {

ILoadRequest::~ILoadRequest() {
    ;
}

LoadRequest::LoadRequest() = default;

LoadRequest::LoadRequest(s32 load_data_alignment, u32 arg_c, bool arg_20)
    : _20(arg_20), mLoadDataAlignment(load_data_alignment) {
    _c = arg_c;
}

}  // namespace ksys::res
