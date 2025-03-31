#include "chess_board_debug.h"

chess_board_debug::chess_board_debug()
{

}
void chess_board_debug::show_chess_board(std_chess_board_position pos)
{
    for(int i=1; i<=256; i++)
    {
        printf("%3d",pos.data[i-1]);
        if(i%16==0)
        printf("\n");
    }
}
