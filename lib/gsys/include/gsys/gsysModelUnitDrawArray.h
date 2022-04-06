#pragma once

#include <hostio/seadHostIONode.h>

namespace gsys {

// TODO
class ModelUnitDrawArray : public sead::hostio::Node {
public:
    struct CreateArg {
        CreateArg();
    };

    ModelUnitDrawArray();
    virtual ~ModelUnitDrawArray();
};

}  // namespace gsys
