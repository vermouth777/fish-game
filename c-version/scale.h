/* =====================================================================
 * 模块：scale.h / scale.c —— 刮鳞评级模块
 * 职责：16 段鳞片的完好度评级（S/A/B/C/raw 五档），品质倍率计算。
 * ===================================================================== */

#ifndef SCALE_H
#define SCALE_H

/* 鳞片分段数 */
#define SCALE_SEGMENTS 16

/* 品质五档：raw/C/B/A/S */
typedef enum {
    QUALITY_RAW = 0,   /* 未处理 */
    QUALITY_C,         /* 破损   */
    QUALITY_B,         /* 普通   */
    QUALITY_A,         /* 上等   */
    QUALITY_S          /* 极上   */
} Quality;

/* 根据完好鳞片占比评定品质 */
Quality    grade_of(float remain_ratio);

/* 品质对应的售价倍率 */
float      quality_mult(Quality q);

/* 品质名，用于输出 */
const char* quality_name(Quality q);

#endif /* SCALE_H */
