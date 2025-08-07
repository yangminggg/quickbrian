#include "chessmovemodel.h"

ChessMoveModel::ChessMoveModel()
{

}
QVector<chess_move> ChessMoveModel::KingMove(std_chess_board_pos &board_pos,unsigned char p)// 将的走法生成
{
    int k;
    unsigned char n;//下一步可能行走的位置
    QVector<chess_move> moves;
    int SideTag = 16 + board_pos.side * 16;	//走棋方，红方16，黑方32
    for(k=0; k<4; k++)//4个方向
    {
        n = p + KingDir[k];	//n为新的可能走到的位置
        if(LegalPosition[board_pos.side][n] & PositionMask[0])	//将对应下标为0
        {
            if(!(board_pos.data[n] & SideTag))	//目标位置上没有本方棋子
            {
                chess_move m = {p,n};
                moves.append(m);
            }
        }
    }
    return moves;
}
QVector<chess_move> ChessMoveModel::AdvisorMove(std_chess_board_pos &board_pos,unsigned char p)// 士的走法生成
{
    int k;
    unsigned char n;//下一步可能行走的位置
    QVector<chess_move> moves;
    int SideTag = 16 + board_pos.side * 16;	//走棋方，红方16，黑方32
    for(k=0; k<4; k++)//4个方向
    {
        n = p + AdvisorDir[k];	//n为新的可能走到的位置
        if(LegalPosition[board_pos.side][n] & PositionMask[1])	//士将对应下标为1
        {
            if(!(board_pos.data[n] & SideTag))	//目标位置上没有本方棋子
            {
                chess_move m = {p,n};
                moves.append(m);
            }
        }
    }
    return moves;
}
QVector<chess_move> ChessMoveModel::BishopMove(std_chess_board_pos &board_pos,unsigned char p)// 相的走法生成
{
    int k;
    unsigned char n;//下一步可能行走的位置
    unsigned char m;//象眼位置
    QVector<chess_move> moves;
    int SideTag = 16 + board_pos.side * 16;	//走棋方，红方16，黑方32
    for(k=0; k<4; k++)//4个方向
    {
        n = p + BishopDir[k];	//n为新的可能走到的位置
        if(LegalPosition[board_pos.side][n] & PositionMask[2])	//象将对应下标为2
        {
            m = p + BishopCheck[k];
            if(!board_pos.data[m])	//象眼位置无棋子占据
            {
                if(!(board_pos.data[n] & SideTag))	//目标位置上没有本方棋子
                {
                    chess_move m = {p,n};
                    moves.append(m);
                }
            }
        }
    }
    return moves;
}
QVector<chess_move> ChessMoveModel::KnightMove(std_chess_board_pos &board_pos,unsigned char p)// 马的走法生成
{
    int k;
    unsigned char n;//下一步可能行走的位置
    unsigned char m;//象眼位置
    QVector<chess_move> moves;
    int SideTag = 16 + board_pos.side * 16;	//走棋方，红方16，黑方32
    for(k=0; k<4; k++)//4个方向
    {
        n = p + BishopDir[k];	//n为新的可能走到的位置
        if(LegalPosition[board_pos.side][n] & PositionMask[2])	//象将对应下标为2
        {
            m = p + BishopCheck[k];
            if(!board_pos.data[m])	//象眼位置无棋子占据
            {
                if( !(board_pos.data[n] & SideTag))	//目标位置上没有本方棋子
                {
                    chess_move m = {p,n};
                    moves.append(m);
                }
            }
        }
    }
    return moves;
}
QVector<chess_move> ChessMoveModel::RookMove(std_chess_board_pos &board_pos,unsigned char p)//车的走法生成
{
    int k,j;
    unsigned char n;//下一步可能行走的位置
    QVector<chess_move> moves;
    int SideTag = 16 + board_pos.side * 16;	//走棋方，红方16，黑方32
    for(k=0; k<4; k++)	//4个方向
    {
        for(j=1; j<10; j++)	//横的最多有8个可能走的位置，纵向最多有9个位置
        {
            n = p + j * RookDir[k];
            if(!(LegalPosition[board_pos.side][n] & PositionMask[4]))	//车士将对应下标为4
                break;//不合理的位置
            if(!board_pos.data[n])	//目标位置上无子
            {
                chess_move m = {p,n};
                moves.append(m);
            }
            else if (board_pos.data[n] & SideTag)	//目标位置上有本方棋子
            {
                break;
            }
            else//目标位置上有对方棋子
            {
                chess_move m = {p,n};
                moves.append(m);
                break;
            }
        }
    }
    return moves;
}
QVector<chess_move> ChessMoveModel::CannonMove(std_chess_board_pos &board_pos,unsigned char p)//炮的走法生成
{
    int k,j;
    unsigned char n;//下一步可能行走的位置
    int SideTag = 16 + board_pos.side * 16;	//走棋方，红方16，黑方32
    int OverFlag;
    QVector<chess_move> moves;
    for(k=0; k<4; k++)	//4个方向
    {
        OverFlag = 0;
        for(j=1; j<10; j++)	//横的最多有8个可能走的位置，纵向最多有9个位置
        {
            n = p + j * CannonDir[k];
            if(!(LegalPosition[board_pos.side][n] & PositionMask[5]))	//炮士将对应下标为5
                break;//不合理的位置
            if(!board_pos.data[n])	//目标位置上无子
            {
                if(!OverFlag)	//未翻山
                {
                    chess_move m = {p,n};
                    moves.append(m);
                }
                //已翻山则不作处理，自动考察向下一个位置
            }
            else//目标位置上有子
            {
                if(!OverFlag)	//未翻山则置翻山标志
                {
                    OverFlag = 1;
                }
                else	//已翻山
                {
                    if(!(board_pos.data[n] & SideTag))//对方棋子
                    {
                        chess_move m = {p,n};
                        moves.append(m);
                    }
                    break;//不论吃不吃子，都退出此方向搜索
                }
            }
        }
    }
    return moves;
}
QVector<chess_move> ChessMoveModel::PawnMove(std_chess_board_pos &board_pos,unsigned char p)//兵的走法生成
{
    int k;
    unsigned char n;//下一步可能行走的位置
    int SideTag = 16 + board_pos.side * 16;	//走棋方，红方16，黑方32
    QVector<chess_move> moves;
    for(k=0; k<3; k++)//3个方向
    {
        n = p + PawnDir[board_pos.side][k];	//n为新的可能走到的位置
        if(LegalPosition[board_pos.side][n] & PositionMask[6])	//兵士将对应下标为6
        {
            if(!(board_pos.data[n] & SideTag))	//目标位置上没有本方棋子
            {
                chess_move m = {p,n};
                moves.append(m);
            }
        }
    }
    return moves;
}
bool ChessMoveModel::Check(std_chess_board_pos &board_pos)//将军检测
{
    unsigned char wKing,bKing; //红黑双方将帅的位置
    unsigned char p,q;
    int r;	//r=1表示将军，否则为0
    int SideTag = 16 + board_pos.side * 16;	//走棋方，红方16，黑方32
    int fSide = 1-board_pos.side;	//对方标志
    int i;
    int PosAdd;	//位置增量

    wKing = board_pos.piece[16];//找到将帅的位置，检查是否有棋子（将帅）
    bKing = board_pos.piece[32];
    if(!wKing || !bKing)//将帅需要存在
    {
        return 0;
    }
    //检测将帅是否照面
    r=1;
    if(wKing%16 == bKing%16)//是否在相同的一列
    {
        for(wKing=wKing-16; wKing!=bKing; wKing=wKing-16)//是否有棋子在同一列
        {
            if(board_pos.data[wKing])//看看同一列有没有棋子挡住
            {
                r=0;
                break;
            }
        }
    }
    q = board_pos.piece[48-SideTag];//lSide方将的位置
    int k;
    unsigned char m;//马腿位置
    unsigned char n;//下一步可能行走的位置
    //5,6是马的位置
    for(i=5;i<=6;i++)
    {
        p = board_pos.piece[SideTag + i];
        if(!p)
        {
            continue;
        }
        for(k=0; k<8; k++)//8个方向
        {
            n = p + KnightDir[k];	//n为新的可能走到的位置
            if(n!=q)//马能够攻击到将
            {
                continue;
            }
            if(LegalPosition[fSide][n] & PositionMask[3])//判读是否在棋盘上，马将对应下标为3
            {
                m = p + KnightCheck[k];//马腿位置
                if(!board_pos.data[m])	//马腿位置无棋子占据
                {
                    return true;
                }
            }
        }
    }
    //检测将是否被车攻击
    r=1;
    for(i=7;i<=8;i++)
    {
        p = board_pos.piece[SideTag + i];//车的位置
        if(!p)
            continue;
        if(p%16 == q%16)	//在同一纵线上
        {
            PosAdd = (p>q?-16:16);
            for(p=p+PosAdd; p!=q; p = p+PosAdd)
            {
                if(board_pos.data[p])	//车将中间有子隔着
                {
                    r=0;
                    break;
                }
            }
            if(r)
                return r;
        }
        else if(p/16 ==q/16)	//在同一横线上
        {
            PosAdd = (p>q?-1:1);
            for(p=p+PosAdd; p!=q; p = p+PosAdd)
            {
                if(board_pos.data[p])
                {
                    r=0;
                    break;
                }
            }
            if(r)
                return r;
        }
    }
    //检测将是否被炮攻击
    int OverFlag = 0;	//翻山标志
    for(i=9;i<=10;i++)
    {
        p = board_pos.piece[SideTag + i];
        if(!p)
            continue;
        if(p%16 == q%16)	//在同一纵线上
        {
            PosAdd = (p>q?-16:16);
            for(p=p+PosAdd; p!=q; p = p+PosAdd)
            {
                if(board_pos.data[p])
                {
                    if(!OverFlag)	//隔一子
                        OverFlag = 1;
                    else			//隔两子
                    {
                        OverFlag = 2;
                        break;
                    }
                }
            }
            if(OverFlag==1)
                return true;
        }
        else if(p/16 ==q/16)	//在同一横线上
        {
            PosAdd = (p>q?-1:1);
            for(p=p+PosAdd; p!=q; p = p+PosAdd)
            {
                if(board_pos.data[p])
                {
                    if(!OverFlag)
                        OverFlag = 1;
                    else
                    {
                        OverFlag = 2;
                        break;
                    }
                }
            }
            if(OverFlag==1)
                return true;
        }
    }

    //检测将是否被兵攻击
    for(i=11;i<=15;i++)
    {
        p = board_pos.piece[SideTag + i];
        if(!p)
            continue;
        for(k=0; k<3; k++)//3个方向
        {
            n = p + PawnDir[fSide][k];	//n为新的可能走到的位置
            if((n==q) && (LegalPosition[fSide][n] & PositionMask[6]))	//兵士将对应下标为6
            {
                return true;
            }
        }
    }
    return 0;
}
















































