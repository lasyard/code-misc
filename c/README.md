# C Programming

## `eight_queen.c`

**八皇后问题**，递归方式实现求解八皇后问题的 CLI 程序。

## `diamond_chess.c`

**独立钻石棋**，递归方式实现求解独立钻石棋的 CLI 程序。

## `game_solution.c`

**数字映射**，求解与两个小游戏有关的数学问题的 CLI 程序。

此程序与以下两个游戏有关：

1. 若干堆硬币，两人轮流“将某堆分为数目不等的两堆”，首先不能执行此操作者输。
2. 一排保龄球瓶，两人轮流“击倒一个或相邻两个瓶”，击倒最后一个或两个者赢。

这里“相邻”的含义是“足够近”。如果两瓶之间曾经有瓶被击倒，则他们不能称为相邻。也可能在游戏开始时，两瓶之间的距离就足够远而不能认为相邻。

The program is related to these 2 games:

1. There are several piles of coins. Two players try to "split one pile into two piles with different number of coins" in turn. The player who cannot do this first lose.
2. There are many bowling pins placed on a line. Two players try to "knock down one or two adjacent pins" in turn. The player who knock down the last one or two win.

Here "adjacent" means "near enough". They are not adjacent if there is any pin knocked down between them. It is possible that at the beginning, the gap between two pins is large enough not to be adjacent.

The result for Game 1:

```
0 -  1   2   4   7  10  20  23  26  50  53
1 -  3   6   9  12  15  28  31  34  37  40  43  46  49  52  55  58  61
2 -  5   8  11  14  17  29  32  35  38  51  54  57  60  63  66  69  72  75  78  81  84  97
3 - 13  16  19  22  25  30  59  62  65  68  71  74  77  86  89  92  95  98
4 - 18  21  24  27  33  36  39  42  45  48  64  67  70  73  76  79  82  85  88  91  94
5 - 41  44  47  56  80  83  96  99
6 -
7 - 87  90  93
```

The result for Game 2:

```
1 -  1,  4,  8
2 -  2,  7, 10
4 -  0,  5
7 -  6, 11
8 -  3,  9
```

Here the numbers on the right are the remainders by 12. There are some exeptions:

```
0 -  0
3 -  3,  6, 18, 39
4 -  9, 21, 57
5 - 28
6 - 11, 22, 34, 70
7 - 15
```

## `hanoi.c`

**汉诺塔**，递归方式实现求解汉诺塔的 CLI 程序。

## `horse_hop.c`

**马踏全盘**，递归方式实现求解马踏全盘问题的 CLI 程序。

## `logic_question.c`

**逻辑推理题**，求解一道逻辑推理题。

请回答下面 10 个问题：

1. 第一个答案是 b 的问题是哪一个？
    (a) 2; (b) 3; (c) 4; (d) 5; (e) 6
2. 唯一的连续两个具有相同答案的问题是：
    (a) 2, 3; (b) 3, 4; (c) 4, 5; (d) 5, 6; (e) 6, 7
3. 本问题答案和哪一个问题的答案相同？
    (a) 1; (b) 2; (c) 4; (d) 7; (e) 6
4. 答案是 a 的问题的个数是：
    (a) 0; (b) 1; (c) 2; (d) 3; (e) 4
5. 本问题答案和哪一个问题的答案相同？
    (a) 10; (b) 9; (c) 8; (d) 7; (e) 6
6. 答案是 a 的问题的个数和答案是什么的问题的个数相同？
    (a) b; (b) c; (c) d; (d) e; (e) 以上都不是
7. 按照字母顺序，本问题的答案和下一个问题的答案相差几个字母？
    (a) 4; (b) 3; (c) 2; (d) 1; (e) 0（例如：a 和 b 相差一个字母）
8. 答案是元音字母的问题的个数是：
    (a) 2; (b) 3; (c) 4; (d) 5; (e) 6（注：a 和 e 是元音字母）
9. 答案是辅音字母的问题的个数是：
    (a) 一个质数；(b) 一个阶乘数；(c) 一个平方数；(d) 一个立方数；(e) 5 的倍数
10. 本问题的答案是：
    (a) a; (b) b; (c) c; (d) d; (e) e

## `magic_square.c`

**幻方**，输出幻方的 CLI 程序。

## `nine_interlocking_rings.c`

**九连环**，递归方式实现求解九连环的 CLI 程序。

## `sudoku.c`

**求解数独**，递归方式实现求解数独问题的 CLI 程序。
