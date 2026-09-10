/* =====================================================================
 * 模块：fish.c —— 鱼种数据模块实现
 * ===================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fish.h"

/* 鱼种总数量 */
#define FISH_COUNT 10

/* 鱼种静态数据表：所有鱼的属性集中在此，改数值不改代码（数据驱动） */
static const Fish FISH_DEFS[FISH_COUNT] = {
    {"minnow",  "小银鱼",   RARITY_1,  20, 1.30f, 0.04f, 0.34f,   9, 0},
    {"crucian", "鲫鱼",     RARITY_1,  35, 1.05f, 0.12f, 0.46f,  16, 0},
    {"grass",   "草鱼",     RARITY_1,  55, 0.92f, 0.24f, 0.58f,  26, 0},
    {"carp",    "锦鲤",     RARITY_2,  90, 0.88f, 0.30f, 0.66f,  42, 1},
    {"eel",     "月鳗",     RARITY_2, 120, 1.15f, 0.58f, 0.94f,  55, 0},
    {"gold",    "金鱼",     RARITY_3, 160, 1.08f, 0.44f, 0.78f,  72, 1},
    {"mkoi",    "月光锦鲤", RARITY_3, 240, 0.82f, 0.36f, 0.74f, 110, 1},
    {"lantern", "灯笼鱼",   RARITY_3, 200, 0.76f, 0.66f, 0.98f,  92, 1},
    {"star",    "流星鱼",   RARITY_4, 340, 1.55f, 0.10f, 0.44f, 155, 1},
    {"moon",    "月神鱼",   RARITY_5, 600, 0.95f, 0.46f, 0.90f, 290, 1}
};

/* 按 id 查找鱼种，找不到返回 NULL（指针的典型用法） */
const Fish* find_fish(const char* id) {
    int i;
    for (i = 0; i < FISH_COUNT; i++) {
        if (strcmp(FISH_DEFS[i].id, id) == 0) {
            return &FISH_DEFS[i];
        }
    }
    return NULL;
}

/* 按稀有度权重随机出一条鱼
 * weights[5] 下标 0~4 分别对应稀有度 1~5 的出现权重 */
const Fish* random_fish(const int weights[5]) {
    int total = 0;
    int i, r, acc = 0;
    for (i = 0; i < 5; i++) {
        total += weights[i];
    }
    if (total <= 0) {
        return &FISH_DEFS[0];   /* 权重异常时兜底返回第一条 */
    }
    r = rand() % total;         /* [0, total) 之间的随机数 */
    for (i = 0; i < FISH_COUNT; i++) {
        /* 每条鱼按它的稀有度权重累加，落点命中即选中 */
        int w = weights[FISH_DEFS[i].rarity - 1];
        acc += w;
        if (r < acc) {
            return &FISH_DEFS[i];
        }
    }
    return &FISH_DEFS[FISH_COUNT - 1];
}

/* 打印全部鱼种表 */
void print_fish_table(void) {
    int i;
    printf("  %-6s %-8s 稀有度  基础分  售价\n", "编号", "名称");
    printf("  ----------------------------------\n");
    for (i = 0; i < FISH_COUNT; i++) {
        const Fish* f = &FISH_DEFS[i];
        printf("  %-6s %-8s  %d星    %3d分   %3d金\n",
               f->id, f->name, f->rarity, f->score, f->price);
    }
}
