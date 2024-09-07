#pragma once

namespace sead {
class Heap;
}

namespace ksys {

struct InitParams {
    sead::Heap* king_sys_heap;
};

// 0x0000007100f3a4e4
bool isGameOver();
// 0x0000007100f3a4f0
void setIsGameOver(bool is_game_over);

void initBaseProcMgr(sead::Heap* heap);

// 0x0000007100f3a8d8
void preInitializeApp(InitParams* params);

}  // namespace ksys
