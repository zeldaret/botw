#include "KingSystem/Physics/System/physDefines.h"

namespace ksys::phys {

const char* contactLayerToText(ContactLayer layer) {
    return layer.text();
}

ContactLayer contactLayerFromText(const sead::SafeString& text) {
    for (auto layer : ContactLayer()) {
        if (text == layer.text())
            return layer;
    }
    return 0;
}

const char* materialToText(Material material) {
    return material.text();
}

Material materialFromText(const sead::SafeString& text) {
    for (auto material : Material()) {
        if (text == material.text())
            return material;
    }
    return 0;
}

const char* floorCodeToText(FloorCode code) {
    return code.text();
}

FloorCode floorCodeFromText(const sead::SafeString& text) {
    for (auto code : FloorCode()) {
        if (text == code.text())
            return code;
    }
    return 0;
}

const char* wallCodeToText(WallCode code) {
    return code.text();
}

WallCode wallCodeFromText(const sead::SafeString& text) {
    for (auto code : WallCode()) {
        if (text == code.text())
            return code;
    }
    return 0;
}

}  // namespace ksys::phys
