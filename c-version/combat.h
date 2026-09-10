/* =====================================================================
 * 模块：combat.h / combat.c —— 连击与计分模块
 * 职责：连击倍率计算、单次抓鱼计分、关卡总分与结局评级。
 * ===================================================================== */

#ifndef COMBAT_H
#define COMBAT_H

/* 连击倍率：连击数越多倍率越高，最高 5 倍 */
int   calc_mult(int combo);

/* 单次抓鱼得分：基础分 × 连击倍率，倍率通过 out_mult 返回 */
int   award_score(int base_score, int combo, int* out_mult);

/* 结局评级：总分/目标分 → S/A/B/C */
char  ending_grade(int total_score, int total_target);

#endif /* COMBAT_H */
