/* =====================================================================
 * 模块：save.h / save.c —— 存档模块
 * 职责：最高分与累计渔获的读写，使用文件持久化（对应课程文件操作）。
 * ===================================================================== */

#ifndef SAVE_H
#define SAVE_H

/* 存档数据结构 */
typedef struct {
    int best_score;     /* 历史最高分 */
    int total_fish;     /* 累计渔获条数 */
    int total_games;    /* 累计游戏局数 */
} SaveData;

/* 读取存档，文件不存在时返回默认值 */
SaveData save_load(void);

/* 保存存档，返回 0 成功、-1 失败 */
int       save_store(const SaveData* data);

#endif /* SAVE_H */
