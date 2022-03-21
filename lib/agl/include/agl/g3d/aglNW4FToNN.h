#pragma once

namespace nn::g3d {
class ResFile;
}

namespace agl::g3d {

class ResFile {
public:
    static void BindTexture(nn::g3d::ResFile*, nn::g3d::ResFile*);
    static void Cleanup(nn::g3d::ResFile*);
};

}  // namespace agl::g3d
