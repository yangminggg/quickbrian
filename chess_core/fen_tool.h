#ifndef FEN_TOOL_H
#define FEN_TOOL_H

#include <stdint.h>
#include <QString>
#include <QDebug>
#include "chess_board_define.h"
#include <string>
/*
FEN是专门用来表示象棋局面的记录规范，在这个规范下，一个局面可以简单地用一行“FEN格式串”
来表示，而不必烦琐地说: “红帅在四路次底线，黑将在5路底线…” 。由于它是文本格式的(只牵涉到很有
限的几个字母、数字和符号)，因此网上传递棋局就非常方便，不用把棋图画在纸上或用文字笨拙地描述了，
而是用棋谱编辑软件摆好局面，自动得到FEN格式串，再贴到诸如Web网页、BBS、电子论坛等能够传递文
字的网络应用平台上。读者面对FEN格式串，只要借助于棋谱编辑软件，用“赋值”和“粘贴”就可以完全
重现局面，使得棋谱交流快速而高效。 (象棋百科全书网站，黄晨，中国象棋计算机应用规范(三) FEN文件
格式)*/

/*
红： R车 N马 B相 A仕 K帅  C炮 P兵
黑： r车 n马 b象 a士 k将  c炮 p卒
再用数字 1--9 来表示空位，从左上角，从左到右，从上到下，一个一个代替进去得到以下排列:
rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR

其中 “/”斜杠的意思是行结束，我们写软件的时都是忽略这个，只是给人看了舒服点而已。
最后这个棋局是轮到谁下棋，轮到红方，后面增加 w ，轮到黑就增加 b

*/

class FEN_TOOL
{
public:
    FEN_TOOL();
    //棋子整数值转换成字符表示
    static char IntToChar(int a)
    {
        if(a <32)
        {
            switch(a)
            {
            case 16:	return 'K';
            case 17:
            case 18:	return 'A';
            case 19:
            case 20:	return 'B';
            case 21:
            case 22:	return 'N';
            case 23:
            case 24:	return 'R';
            case 25:
            case 26:	return 'C';
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:	return 'P';
            default:	return 0;
            }
        }
        else
        {
            a = a-16;
            switch(a)
            {
            case 16:	return 'k';
            case 17:
            case 18:	return 'a';
            case 19:
            case 20:	return 'b';
            case 21:
            case 22:	return 'n';
            case 23:
            case 24:	return 'r';
            case 25:
            case 26:	return 'c';
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:	return 'p';
            default:	return 0;
            }
        }
    }
    static int CharToSubscript(char ch)
    {
        switch(ch)
        {
        case 'k':
        case 'K':return 0;
        case 'a':
        case 'A':return 1;
        case 'b':
        case 'B':return 2;
        case 'n':
        case 'N':return 3;
        case 'r':
        case 'R':return 4;
        case 'c':
        case 'C':return 5;
        case 'p':
        case 'P':return 6;
        default:return 7;
        }
    }
    //将FEN串表示的局面转换成一维数组
    static void StringToArray(std_chess_board_pos &pos,const char *FenStr)
    {
        int i, j, k;
        int pcWhite[7]={16,17,19,21,23,25,27};
        int pcBlack[7]={32,33,35,37,39,41,43};
        const char *str;
        for (i = 0; i < 256; i ++)
        {
            pos.data[i] = 0;
        }
        str = FenStr;
        if (*str == '\0')
        {
            return;
        }

        i = 3;
        j = 3;
        while (*str != ' ')
        {
            if (*str == '/')
            {
                j = 3;
                i ++;
                if (i > 12)
                {
                    break;
                }
            }
            else if (*str >= '1' && *str <= '9')
            {
                for (k = 0; k < (*str - '0'); k ++)
                {
                    if (j >= 11)
                    {
                        break;
                    }
                    j ++;
                }
            }
            else if (*str >= 'A' && *str <= 'Z')
            {
                if (j <= 11)
                {
                    k = CharToSubscript(*str);
                    if (k < 7)
                    {
                        if (pcWhite[k] < 32)
                        {
                            pos.data[(i<<4) + j] = pcWhite[k];
                            pcWhite[k]++;
                        }
                    }
                    j ++;
                }
            }
            else if (*str >= 'a' && *str <= 'z')
            {
                if (j <= 11)
                {
                    k = CharToSubscript(*str);
                    if (k < 7)
                    {
                        if (pcBlack[k] < 48)
                        {
                            pos.data[(i<<4) + j] = pcBlack[k];
                            pcBlack[k]++;
                        }
                    }
                    j ++;
                }
            }

            str ++;
            if (*str == '\0')
            {
                return;
            }
        }
        str ++;

        if (*str == 'b')
            pos.side = 1;
        else
            pos.side = 0;
    }
    // 将一维数组表示的局面转换成FEN串
    static void ArrayToString(std_chess_board_pos &pos,char *res,int side)//轮到哪方走，0表示红方，1表示黑方
    {
        int i, j, k, pc;
        char *str;
        char FenString[128];		//局面的FEN串格式

        str = FenString;
        for (i = 3; i <= 12; i ++)
        {
            k = 0;
            for (j = 3; j <= 11; j ++)
            {
                pc = pos.data[(i << 4) + j];
                if (pc != 0)
                {
                    if (k > 0)
                    {
                        *str = k + '0';
                        str ++;
                        k = 0;
                    }
                    *str = IntToChar(pc);
                    str ++;
                }
                else
                {
                    k ++;
                }
            }
            if (k > 0)
            {
                *str = k + '0';
                str ++;
            }
            *str = '/';
            str ++;
        }
        str --;
        *str = ' ';
        str ++;
        *str = (side == 0 ? 'w' : 'b');
        str ++;
        *str = '\0';
        strcpy(res,FenString);
    }
    static void OutputBoard(std_chess_board_pos &pos)
    {
        for(int i=1; i<=256; i++)
        {
            qDebug("%3d",pos.data[i-1]);
            if(i%16==0)
                qDebug("\n");
        }
    }
    static void test(void)
    {
        std_chess_board_pos pos;
        StringToArray(pos,"rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1");
        OutputBoard(pos);
        char FenString[128];		//局面的FEN串格式
        ArrayToString(pos,FenString,0);
    }

};
#endif // FEN_TOOL_H
