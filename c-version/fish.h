/* =====================================================================
 * 月湖夜钓（Moonlake Fishing）—— C 语言版
 * ---------------------------------------------------------------------
 * 模块：fish.h / fish.c —— 鱼种数据模块
 * 职责：定义鱼的结构体、10 种鱼的静态数据表，以及按 id 查找鱼、
 *       按关卡权重随机生成一条鱼。
 * ===================================================================== */

#ifndef FISH_H
#define FISH_H

/* 鱼种稀有度：对应课程中的「枚举类型」知识点 */
typedef enum {
    RARITY_1 = 1,   /* 普通 */
    RARITY_2,       /* 少见 */
    RARITY_3,       /* 稀有 */
    RARITY_4,       /* 珍稀 */
    RARITY_5        /* 传说 */
} Rarity;

/* 鱼的结构体：对应课程中的「结构体」知识点 */
typedef struct {
    char    id[16];        /* 唯一标识     */
    char    name[16];      /* 显示名称     */
    Rarity  rarity;        /* 稀有度       */
    int     score;         /* 基础分值     */
    float   speed;         /* 速度倍率     */
    float   depth_min;     /* 活动深度下限 */
    float   depth_max;     /* 活动深度上限 */
    int     price;         /* 基础售价     */
    int     has_glow;      /* 是否发光(稀有鱼) */
} Fish;

/* 对外接口 */
const Fish* find_fish(const char* id);          /* 按 id 查找鱼，找不到返回 NULL */
const Fish* random_fish(const int weights[5]);  /* 按稀有度权重随机出一条鱼 */
void        print_fish_table(void);             /* 打印全部鱼种表 */

#endif /* FISH_H */
