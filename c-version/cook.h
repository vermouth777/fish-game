/* =====================================================================
 * 模块：cook.h / cook.c —— 菜谱与烹饪模块
 * 职责：菜谱数据表、按鱼查菜谱、烹饪售价计算（基础价×品质×菜谱倍率）。
 * ===================================================================== */

#ifndef COOK_H
#define COOK_H

#include "scale.h"   /* 需要 Quality 类型 */

/* 菜谱结构体 */
typedef struct {
    char    id[16];        /* 菜谱标识   */
    char    name[24];      /* 菜名       */
    char    need[16];      /* 所需鱼 id  */
    Quality min_quality;   /* 最低品质门槛 */
    float   mult;          /* 售价倍率   */
} Recipe;

/* 按鱼 id 查找可做的菜谱，找不到返回 NULL */
const Recipe* find_recipe(const char* fish_id);

/* 计算烹饪售价：基础价 × 品质倍率 × 菜谱倍率
 * 若鱼不满足最低品质门槛，返回 -1 表示不能做这道菜 */
int cook_price(const char* fish_id, Quality q, const Recipe* recipe);

/* 打印全部菜谱 */
void print_recipe_table(void);

#endif /* COOK_H */
