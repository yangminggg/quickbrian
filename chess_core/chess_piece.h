#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

/* ID号定义
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
n马 37 38
b象 35 36
a士 33 34
k将 32
c炮 41 42
p卒 43 44 45 46 47

红方棋子 & 16 == 1
黑方棋子 & 32 == 1
*/
#include <QString>


class chess_piece
{
public:
    chess_piece()
    {

    }
    ~chess_piece()
    {

    }
    enum m_emTYPE{JIANG, SHI, XIANG, MA, CHE, PAO, BING};
    static QString getName(enum m_emTYPE type,int id)
    {
        if((id& 16) == 16)
        {
            switch (type) {
            case CHE:
                return "车";
            case MA:
                return "马";
            case PAO:
                return "炮";
            case BING:
                return "兵";
            case JIANG:
                return "帅";
            case SHI:
                return "仕";
            case XIANG:
                return "相";
            default:
                return "ERROR";
            }
        }
        else if((id& 32) == 32)
        {
            switch (type) {
            case CHE:
                return "车";
            case MA:
                return "马";
            case PAO:
                return "炮";
            case BING:
                return "卒";
            case JIANG:
                return "将";
            case SHI:
                return "士";
            case XIANG:
                return "象";
            default:
                return "ERROR";
            }
        }
        return "ERROR";
    }
    static chess_piece BuildChessPiece(enum m_emTYPE type_,int id_,int m_nRow_,int m_nCol_,double value_)
    {
        chess_piece data;
        data.type = type_;
        data.id = id_;
        data.m_nRow = m_nRow_;
        data.m_nCol = m_nCol_;
        data.value = value_;
        data.name = getName(data.type,data.id);
        return data;
    }
public:
    enum m_emTYPE type;
    int  id;//ID号
    int  m_nRow;//行
    int  m_nCol;//列
    double value;//权重
    QString name;
};

#endif // CHESS_PIECE_H
