#ifndef CHESSMOVEMODEL_H
#define CHESSMOVEMODEL_H
#include "chess_core/chess_board_define.h"
#include <QVector>

class ChessMoveModel
{
public:
    ChessMoveModel();
    //棋子走法生成函数
    QVector<chess_move> KingMove(std_chess_board_pos &board_pos,unsigned char p);// 将的走法生成，unsigned char p 代表当前将帅（棋子）的位置
    QVector<chess_move> AdvisorMove(std_chess_board_pos &board_pos,unsigned char p);// 士的走法生成
    QVector<chess_move> BishopMove(std_chess_board_pos &board_pos,unsigned char p);// 象的走法生成
    QVector<chess_move> KnightMove(std_chess_board_pos &board_pos,unsigned char p);// 马的走法生成
    QVector<chess_move> RookMove(std_chess_board_pos &board_pos,unsigned char p);// 车的走法生成
    QVector<chess_move> CannonMove(std_chess_board_pos &board_pos,unsigned char p);// 炮的走法生成
    QVector<chess_move> PawnMove(std_chess_board_pos &board_pos,unsigned char p);// 兵的走法生成
    bool Check(std_chess_board_pos &board_pos);//将军检测，true 出现将军局面，false没有出现将军局面，后续需要完善受到什么危险，哪个子造成的危险
public:

    //----------------走法生成相关辅助数组---------------------------------------------
    //各种棋子走法数组
    short KingDir[8] ={-0x10,		-0x01,	+0x01,	+0x10,	0,		0,		0,		0},//将
          AdvisorDir[8]={-0x11,		-0x0f,	+0x0f,	+0x11,	0,		0,		0,		0},		//士
          BishopDir[8] ={-0x22,		-0x1e,	+0x1e,	+0x22,	0,		0,		0,		0},	//象
          KnightDir[8] ={-0x21,		-0x1f,	-0x12,	-0x0e,	+0x0e,	+0x12,	+0x1f,	+0x21},	//马
          RookDir[8]   ={-0x01,		+0x01,	-0x10,	+0x10,	0,		0,		0,		0},		//车
          CannonDir[8] ={-0x01,		+0x01,	-0x10,	+0x10,	0,		0,		0,		0},		//炮
          PawnDir[2][8]={
                {-0x01,		+0x01,	-0x10,	0,		0,		0,		0,		0},
                {-0x01,		+0x01,	+0x10,	0,		0,		0,		0,		0}
            };		//兵

    short KnightCheck[8] = {-0x10,-0x10,-0x01,+0x01,-0x01,+0x01,+0x10,+0x10};//马腿位置
    short BishopCheck[8] = {-0x11,-0x0f,+0x0f,+0x11,0,0,0,0};	//象眼位置
    short kingpalace[9] = {54,55,56,70,71,72,86,87,88};	//黑方九宫位置

    //各种棋子合理位置数组
    unsigned char LegalPosition[2][256] ={
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
            0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
            0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
            0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
            0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
            0, 0, 0, 9, 1,25, 1, 9, 1,25, 1, 9, 0, 0, 0, 0,
            0, 0, 0, 9, 1, 9, 1, 9, 1, 9, 1, 9, 0, 0, 0, 0,
            0, 0, 0, 17, 1, 1, 7, 19, 7, 1, 1, 17, 0, 0, 0, 0,
            0, 0, 0, 1, 1, 1, 3, 7, 3, 1, 1, 1, 0, 0, 0, 0,
            0, 0, 0, 1, 1, 17, 7, 3, 7, 17, 1, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 1, 17, 7, 3, 7, 17, 1, 1, 0, 0, 0, 0,
            0, 0, 0, 1, 1, 1, 3, 7, 3, 1, 1, 1, 0, 0, 0, 0,
            0, 0, 0, 17, 1, 1, 7, 19, 7, 1, 1, 17, 0, 0, 0, 0,
            0, 0, 0, 9, 1, 9, 1, 9, 1, 9, 1, 9, 0, 0, 0, 0,
            0, 0, 0, 9, 1,25, 1, 9, 1,25, 1, 9, 0, 0, 0, 0,
            0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
            0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
            0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
            0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
            0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        }
    };
    unsigned char PositionMask[7] = {2, 4, 16, 1, 1, 1, 8};
};

#endif // CHESSMOVEMODEL_H
