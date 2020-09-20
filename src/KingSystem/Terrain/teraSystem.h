#pragma once

namespace sead {
class Heap;
}

namespace ksys::tera {

// TODO:
class ApertureMaps {
    void updateMap();
};
class ApertureMapsCollector {
    void allocateImage();
    void releaseImage();
};
class Core {
    class Grass;
    class Model;
    class Tree;
};
class ImageResourceMgr {
    void procUnloadResidualRequest();
};
class ResourceHolder;
class Scene {
    void exportFileBinary();
};
class System {
public:
    static System* instance();
    void allocateApertureMapsCollectorImage(sead::Heap* heap);
    void loadScene();
};
class Water {
    void setUpAttributeTable();
};

bool checkTeraSystemStatus();

}  // namespace ksys::tera
