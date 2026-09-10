/* =====================================================================
 * 模块：combat.c —— 连击与计分模块实现
 * ===================================================================== */

#include <stddef.h>   /* NULL */
#include "combat.h"

/* 连击倍率：对应网页版 calcMult
 * combo>=8 → ×5，>=5 → ×4，>=3 → ×3，>=2 → ×2，否则 ×1 */
int calc_mult(int combo) {
    if (combo >= 8) return 5;
    if (combo >= 5) return 4;
    if (combo >= 3) return 3;
    if (combo >= 2) return 2;
    return 1;
}

/* 单次抓鱼得分 */
int award_score(int base_score, int combo, int* out_mult) {
    int mult = calc_mult(combo);
    if (out_mult != NULL) {
        *out_mult = mult;
    }
    return base_score * mult;
}

/* 结局评级：ratio = 总分/目标分
 * >=1.75 → S，>=1.35 → A，>=1.00 → B，否则 C */
char ending_grade(int total_score, int total_target) {
    float ratio = (float)total_score / (float)total_target;
    if (ratio >= 1.75f) return 'S';
    if (ratio >= 1.35f) return 'A';
    if (ratio >= 1.00f) return 'B';
    return 'C';
}
