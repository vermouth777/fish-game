/* =====================================================================
 * 模块：save.c —— 存档模块实现
 * 使用 fopen/fscanf/fprintf 实现文件读写，对应课程「文件操作」。
 * ===================================================================== */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "save.h"

/* 存档文件名 */
#define SAVE_FILE "moonlake_save.txt"

/* 读取存档 */
SaveData save_load(void) {
    SaveData d;
    FILE* fp;
    /* 先给默认值 */
    d.best_score = 0;
    d.total_fish = 0;
    d.total_games = 0;

    fp = fopen(SAVE_FILE, "r");
    if (fp == NULL) {
        return d;   /* 文件不存在，返回默认值 */
    }
    /* 读三个整数，读不到就保留默认值 */
    fscanf(fp, "%d %d %d", &d.best_score, &d.total_fish, &d.total_games);
    fclose(fp);
    return d;
}

/* 保存存档 */
int save_store(const SaveData* data) {
    FILE* fp = fopen(SAVE_FILE, "w");
    if (fp == NULL) {
        return -1;   /* 打开失败 */
    }
    fprintf(fp, "%d %d %d\n",
            data->best_score, data->total_fish, data->total_games);
    fclose(fp);
    return 0;
}
