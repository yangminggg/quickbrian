#ifndef CHESS_BOARD_DEBUG_H
#define CHESS_BOARD_DEBUG_H

#include "chess_board_define.h"
#include <QWidget>
//调试象棋，使用界面等显示
class chess_board_debug
{
public:
    chess_board_debug();
    static void show_chess_board(std_chess_board_position pos);
};

#endif // CHESS_BOARD_DEBUG_H



