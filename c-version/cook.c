/* =====================================================================
 * 模块：cook.c —— 菜谱与烹饪模块实现
 * ===================================================================== */

#include <stdio.h>
#include <string.h>
#include "cook.h"
#include "fish.h"   /* 需要 find_fish 获取鱼的基础价 */

/* 菜谱数量 */
#define RECIPE_COUNT 10

/* 菜谱数据表 */
static const Recipe RECIPES[RECIPE_COUNT] = {
    {"r_minnow",  "银鱼煎饼",   "minnow",  QUALITY_B, 1.85f},
    {"r_crucian", "鲫鱼豆腐汤", "crucian", QUALITY_B, 1.90f},
    {"r_grass",   "草鱼生鱼片", "grass",   QUALITY_A, 2.25f},
    {"r_carp",    "锦鲤刺身",   "carp",    QUALITY_A, 2.10f},
    {"r_eel",     "蒲烧月鳗",   "eel",     QUALITY_B, 2.35f},
    {"r_gold",    "金丝鱼球",   "gold",    QUALITY_A, 2.15f},
    {"r_mkoi",    "月光鱼冻",   "mkoi",    QUALITY_A, 2.25f},
    {"r_lantern", "灯笼鱼锅",   "lantern", QUALITY_B, 2.45f},
    {"r_star",    "流星炙烤",   "star",    QUALITY_A, 2.65f},
    {"r_moon",    "月神全席",   "moon",    QUALITY_S, 3.10f}
};

/* 按鱼 id 查找可做的菜谱 */
const Recipe* find_recipe(const char* fish_id) {
    int i;
    for (i = 0; i < RECIPE_COUNT; i++) {
        if (strcmp(RECIPES[i].need, fish_id) == 0) {
            return &RECIPES[i];
        }
    }
    return NULL;
}

/* 计算烹饪售价
 * 若鱼品质不满足菜谱最低门槛，返回 -1 表示不能做 */
int cook_price(const char* fish_id, Quality q, const Recipe* recipe) {
    const Fish* fish = find_fish(fish_id);
    if (fish == NULL || recipe == NULL) {
        return -1;
    }
    /* 品质门槛检查 */
    if (q < recipe->min_quality) {
        return -1;   /* 品质不够，不能做这道菜 */
    }
    return (int)(fish->price * quality_mult(q) * recipe->mult);
}

/* 打印全部菜谱 */
void print_recipe_table(void) {
    int i;
    printf("  %-12s %-6s  最低品质  售价倍率\n", "菜名", "所需鱼");
    printf("  ----------------------------------\n");
    for (i = 0; i < RECIPE_COUNT; i++) {
        const Recipe* r = &RECIPES[i];
        const Fish* f = find_fish(r->need);
        printf("  %-12s %-6s   %s   ×%.2f\n",
               r->name, f ? f->name : "?", quality_name(r->min_quality), r->mult);
    }
}
