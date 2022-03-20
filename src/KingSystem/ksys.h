#pragma once

namespace sead {
class Heap;
}

namespace ksys {

// 0x0000007100f3a4e4
bool isGameOver();
// 0x0000007100f3a4f0
void setIsGameOver(bool is_game_over);

void initBaseProcMgr(sead::Heap* heap);

}  // namespace ksys
