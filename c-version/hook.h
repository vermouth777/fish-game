/* =====================================================================
 * 模块：hook.h / hook.c —— 鱼钩状态机模块
 * 职责：定义鱼钩的 5 个状态（idle/dropping/sunk/biting/reeling），
 *       实现状态转移函数，对应课程中的「enum + switch 状态机」。
 * ===================================================================== */

#ifndef HOOK_H
#define HOOK_H

/* 鱼钩状态机：五个状态 */
typedef enum {
    HOOK_IDLE,      /* 待抛   */
    HOOK_DROPPING,  /* 下沉   */
    HOOK_SUNK,      /* 沉底   */
    HOOK_BITING,    /* 咬钩   */
    HOOK_REELING    /* 收竿   */
} HookState;

/* 触发事件：c=抛竿 d=沉底 b=咬钩 r=收竿 t=超时 */
typedef enum {
    EVT_CAST = 'c',
    EVT_SINK = 'd',
    EVT_BITE = 'b',
    EVT_REEL = 'r',
    EVT_TIME = 't'
} HookEvent;

/* 状态转移：返回新状态 */
HookState    hook_transition(HookState cur, HookEvent evt);
const char*  hook_state_name(HookState s);   /* 状态名，用于输出 */

#endif /* HOOK_H */
