#include "KingSystem/System/KingEditor.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(KingEditor)

void KingEditor::init(sead::Heap* heap) {
    // Stubbed in release.
}

void KingEditor::calc() {
    // Stubbed in release.
}

void KingEditor::registerComponent(KingEditorComponent* component) {
    // Stubbed in release.
}

void KingEditor::log(const char* system, const char* message, void*, int) {
    // Stubbed in release.
}

void KingEditorComponent::log(const char* message, void* x, int y) const {
    KingEditor::instance()->log(getName(), message, x, y);
}

}  // namespace ksys
