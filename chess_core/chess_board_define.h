#ifndef CHESS_BOARD_DEFINE
#define CHESS_BOARD_DEFINE

//使用值定义象棋棋子
/*
红：
R车 23 24
N马 21 22
B相 19 20
A仕 17 18
K帅 16
C炮 25 26
P兵 27 28 29 30 31

黑：
r车 39 40
n马 21 22
b象 36 36
a士 33 34
k将 32
c炮 41 42
p卒 43 44 45 46 47

红方棋子 & 16 == 1
黑方棋子 & 32 == 1
*/

//使用一维数组表示16*16标准矩阵


enum e_board_side_define
{
    CHESS_RED_SIDE     = 0,
    CHESS_BLACK_SIDE   = 1
};

typedef struct
{
   unsigned char  from, to;
}chess_move;

typedef struct std_chess_board_position
{
    char data[256] = {0};//棋盘位置和棋子，使用16*16棋盘
    unsigned char piece[48];	//棋子数组，保存双方的每一个棋子的位置，如果棋子被吃掉，则其值为0。16~31保存红方对应棋子位置，32~47保存黑方对应棋子位置，为了棋子的值和位置保持一致。
    int side;//轮到哪方走，0表示红方，1表示黑方
}std_chess_board_pos;
#endif // CHESS_BOARD_DEFINE

