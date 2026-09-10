/* =====================================================================
 * 月湖夜钓（Moonlake Fishing）—— C 语言版
 * ---------------------------------------------------------------------
 * 课程   ：基于 C 语言的游戏开发实践
 * 作者   ：杨君平（GitHub: YJP-777123）
 *
 * 主程序 main.c：负责游戏主菜单、关卡流程、玩家交互，串联各模块。
 *
 * 玩法（命令行文字版）：
 *   共有 3 个关卡，每关玩家多次抛竿钓鱼。
 *   抛竿后等待鱼上钩，鱼咬钩时需在限定次数内输入 r 收竿。
 *   成功则随机获得一条鱼（按关卡稀有度权重），按连击倍率计分。
 *   收竿失败则连击中断。三关结束按总分结算 S/A/B/C 结局。
 *
 * 编译（Visual Studio 需加 /utf-8 以正确解析中文）：
 *   cl /utf-8 main.c fish.c hook.c combat.c scale.c cook.c save.c
 * ===================================================================== */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "fish.h"
#include "hook.h"
#include "combat.h"
#include "scale.h"
#include "cook.h"
#include "save.h"

/* 关卡结构体 */
typedef struct {
    char chap[16];       /* 章节标记 */
    char name[32];       /* 章节名   */
    int  target;         /* 目标分   */
    int  casts;          /* 本关抛竿次数 */
    int  weights[5];     /* 各稀有度权重(下标0~4对应稀有度1~5) */
} Level;

/* 三个关卡的数据表 */
static const Level LEVELS[3] = {
    {"CHAPTER 1", "第一章 · 初见月色",  600, 8, {70, 26,  4,  0, 0}},
    {"CHAPTER 2", "第二章 · 水母暗涌", 1150, 10, {44, 34, 17,  5, 0}},
    {"CHAPTER 3", "第三章 · 月神降临", 1700, 12, {26, 30, 26, 14, 4}}
};

/* 清空输入缓冲区（吃掉多余换行） */
static void flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* 丢弃 */
    }
}

/* 等待玩家按任意键继续 */
static void press_any_key(void) {
    printf("  按回车继续...");
    flush_input();
}

/* 主菜单：返回玩家选择 1/2/3 */
static int main_menu(void) {
    int choice = 0;
    printf("\n");
    printf("  ============================================\n");
    printf("    月湖夜钓 · Moonlake Fishing（C 语言版）\n");
    printf("  ============================================\n");
    printf("    1. 开始夜钓\n");
    printf("    2. 查看鱼种图鉴\n");
    printf("    3. 查看菜谱\n");
    printf("    0. 退出游戏\n");
    printf("  --------------------------------------------\n");
    printf("  请选择：");
    if (scanf("%d", &choice) != 1) {
        choice = 0;
    }
    flush_input();
    return choice;
}

/* 一关的钓鱼流程：返回本关得分 */
static int play_level(const Level* lv) {
    int i;
    int score = 0;
    int combo = 0;
    int caught = 0;
    HookState hook = HOOK_IDLE;
    SaveData save;

    printf("\n");
    printf("  ====== %s  %s ======\n", lv->chap, lv->name);
    printf("  目标：%d 分 | 共 %d 次抛竿机会\n\n", lv->target, lv->casts);

    for (i = 1; i <= lv->casts; i++) {
        char input;
        int mult = 1;
        const Fish* fish;
        int bite_wait;      /* 咬钩前等待的"刻度"数 */
        int j;

        printf("  [第 %d/%d 竿] 当前连击 %d 次 | 输入 c 抛竿，q 退出本关\n",
               i, lv->casts, combo);
        printf("  > ");
        scanf(" %c", &input);
        flush_input();
        if (input == 'q' || input == 'Q') {
            break;
        }
        if (input != 'c' && input != 'C') {
            printf("  （无效输入，跳过本竿）\n\n");
            continue;
        }

        /* 抛竿：状态机 idle -> dropping */
        hook = hook_transition(hook, EVT_CAST);
        printf("  抛竿！鱼钩 %s...\n", hook_state_name(hook));

        /* 下沉：dropping -> sunk */
        hook = hook_transition(hook, EVT_SINK);
        printf("  鱼钩 %s，等待鱼上钩...\n", hook_state_name(hook));

        /* 随机等待一段时间（模拟鱼靠近的过程） */
        bite_wait = 2 + rand() % 4;   /* 2~5 个刻度 */
        for (j = 0; j < bite_wait; j++) {
            printf("    ...\n");
        }

        /* 是否咬钩：约 70% 概率有鱼咬钩，30% 空等超时 */
        if (rand() % 10 < 7) {
            hook = hook_transition(hook, EVT_BITE);
            printf("  💥 鱼咬钩了！%s！\n", hook_state_name(hook));
            printf("  快输入 r 收竿（只有一次机会！）\n  > ");

            scanf(" %c", &input);
            flush_input();
            if (input == 'r' || input == 'R') {
                /* 及时收竿成功 */
                hook = hook_transition(hook, EVT_REEL);
                fish = random_fish(lv->weights);
                combo++;
                caught++;
                {
                    int earned = award_score(fish->score, combo, &mult);
                    score += earned;
                    printf("  收竿！钓到【%s】（稀有度%d星，基础%d分）\n",
                           fish->name, fish->rarity, fish->score);
                    printf("  连击 %d 次，倍率 ×%d，本竿 +%d 分！\n",
                           combo, mult, earned);
                }
                hook = hook_transition(hook, EVT_REEL);   /* reeling -> idle */
            } else {
                /* 脱钩，连击中断 */
                hook = hook_transition(hook, EVT_TIME);
                combo = 0;
                printf("  鱼脱钩了！连击中断。\n");
            }
        } else {
            /* 空等超时 */
            hook = hook_transition(hook, EVT_TIME);
            printf("  等了好久没有鱼，收竿吧（连击中断）。\n");
            combo = 0;
        }
        printf("  当前得分：%d\n\n", score);
    }

    printf("  -------- 本关结算 --------\n");
    printf("  钓到 %d 条鱼，本关得分 %d 分（目标 %d 分）\n",
           caught, score, lv->target);
    if (score >= lv->target) {
        printf("  ✓ 达成目标！\n");
    } else {
        printf("  ✗ 未达成目标。\n");
    }

    /* 刷新存档里的累计渔获 */
    save = save_load();
    save.total_fish += caught;
    save.total_games += 1;
    if (score > save.best_score) {
        save.best_score = score;
        printf("  🏆 新纪录！历史最高分刷新为 %d 分\n", score);
    }
    save_store(&save);

    return score;
}

/* 查看图鉴 */
static void show_codex(void) {
    printf("\n  ====== 鱼种图鉴 ======\n\n");
    print_fish_table();
    printf("\n");
    press_any_key();
}

/* 查看菜谱 */
static void show_recipes(void) {
    printf("\n  ====== 菜谱 ======\n\n");
    print_recipe_table();
    printf("\n");
    press_any_key();
}

/* 结算结局 */
static void show_ending(int total_score, int total_target) {
    char grade = ending_grade(total_score, total_target);
    printf("\n");
    printf("  ============================================\n");
    printf("    三夜结束 · 总分 %d / 目标 %d\n", total_score, total_target);
    printf("    结局评级：[%c]\n", grade);
    printf("  ============================================\n");
    switch (grade) {
        case 'S': printf("    月光渔王！湖上从此有了你的传说。\n"); break;
        case 'A': printf("    月下高手！月神鱼似乎已对你侧目。\n"); break;
        case 'B': printf("    夜钓之人。鱼不多，但夜很安静。\n"); break;
        default:  printf("    初识月色。传说还远，但夜还很长。\n"); break;
    }
    printf("\n");
}

int main(void) {
    int choice;
    int total_score = 0;
    int total_target = 0;
    int i;

    /* 用当前时间作随机种子（课程知识点：srand/rand） */
    srand((unsigned)time(NULL));

    printf("  （C 语言版月湖夜钓 已启动）\n");

    while (1) {
        choice = main_menu();
        if (choice == 0) {
            printf("  感谢游玩，再见！\n");
            break;
        } else if (choice == 2) {
            show_codex();
        } else if (choice == 3) {
            show_recipes();
        } else if (choice == 1) {
            /* 开始游戏：三关依次进行 */
            total_score = 0;
            total_target = 0;
            for (i = 0; i < 3; i++) {
                total_score += play_level(&LEVELS[i]);
                total_target += LEVELS[i].target;
            }
            show_ending(total_score, total_target);
        } else {
            printf("  无效选择，请重新输入。\n");
        }
    }

    return 0;
}
