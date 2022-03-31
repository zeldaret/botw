#pragma once

namespace nn::g3d {

class WorldMtxManip;

class ICalculateWorldCallback {
public:
    // TODO
    struct CallbackArg;

    virtual ~ICalculateWorldCallback() = 0;
    virtual void Exec(CallbackArg& arg, WorldMtxManip& manip) = 0;
};

}  // namespace nn::g3d
