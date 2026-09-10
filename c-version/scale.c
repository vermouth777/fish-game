/* =====================================================================
 * 模块：scale.c —— 刮鳞评级模块实现
 * ===================================================================== */

#include "scale.h"

/* 根据完好鳞片占比评定品质（16 段鳞片）
 * 完好率 >=90% → S，>=80% → A，>=60% → B，>=40% → C，否则 raw */
Quality grade_of(float remain_ratio) {
    if (remain_ratio >= 0.90f) return QUALITY_S;
    if (remain_ratio >= 0.80f) return QUALITY_A;
    if (remain_ratio >= 0.60f) return QUALITY_B;
    if (remain_ratio >= 0.40f) return QUALITY_C;
    return QUALITY_RAW;
}

/* 品质对应的售价倍率（switch 多分支） */
float quality_mult(Quality q) {
    switch (q) {
        case QUALITY_S:   return 2.00f;
        case QUALITY_A:   return 1.50f;
        case QUALITY_B:   return 1.05f;
        case QUALITY_C:   return 0.60f;
        case QUALITY_RAW: return 0.50f;
        default:          return 1.00f;
    }
}

/* 品质名 */
const char* quality_name(Quality q) {
    switch (q) {
        case QUALITY_S:   return "S(极上)";
        case QUALITY_A:   return "A(上等)";
        case QUALITY_B:   return "B(普通)";
        case QUALITY_C:   return "C(破损)";
        case QUALITY_RAW: return "raw(未处理)";
        default:          return "未知";
    }
}
