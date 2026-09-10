/* =====================================================================
 * 模块：hook.c —— 鱼钩状态机模块实现
 * ===================================================================== */

#include "hook.h"

/* 状态转移表：给定当前状态和触发事件，返回下一个状态
 * 这是课程中「enum + switch 状态机」的经典写法 */
HookState hook_transition(HookState cur, HookEvent evt) {
    switch (cur) {
        case HOOK_IDLE:
            if (evt == EVT_CAST) return HOOK_DROPPING;
            break;
        case HOOK_DROPPING:
            if (evt == EVT_SINK) return HOOK_SUNK;
            break;
        case HOOK_SUNK:
            if (evt == EVT_BITE) return HOOK_BITING;   /* 鱼咬钩 */
            if (evt == EVT_TIME) return HOOK_IDLE;     /* 超时，鱼跑了 */
            break;
        case HOOK_BITING:
            if (evt == EVT_REEL) return HOOK_REELING;  /* 及时收竿 */
            if (evt == EVT_TIME) return HOOK_IDLE;     /* 脱钩 */
            break;
        case HOOK_REELING:
            if (evt == EVT_REEL) return HOOK_IDLE;     /* 收竿完成 */
            break;
        default:
            break;
    }
    return cur;   /* 非法事件，状态保持不变 */
}

/* 状态名转字符串 */
const char* hook_state_name(HookState s) {
    switch (s) {
        case HOOK_IDLE:     return "待抛(idle)";
        case HOOK_DROPPING: return "下沉(dropping)";
        case HOOK_SUNK:     return "沉底(sunk)";
        case HOOK_BITING:   return "咬钩(biting)";
        case HOOK_REELING:  return "收竿(reeling)";
        default:            return "未知";
    }
}
