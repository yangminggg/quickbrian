#include "ChessBoard.h"
#include "ui_ChessBoard.h"
#include <QDebug>

ChessBoard::ChessBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChessBoard)
{
    ui->setupUi(this);
}

ChessBoard::~ChessBoard()
{
    delete ui;
}
void ChessBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    qDebug()<<"paint event...";
    int side = qMin(int((ui->centralwidget->width()) / 0.9), ui->label->height());
    painter.scale(side / 960.0, side / 960.0);

    m_nOffSet = 60;  //距离界面的边距
    m_nD = 90;       //间距为50px
    m_nR = m_nD/2;   //棋子半径为d/2

    //*******************绘画棋盘*******************
    //绘画10条横线
    for(int i = 0; i <= 9; i++)
    {
        painter.drawLine(QPoint(m_nOffSet, m_nOffSet+i*m_nD), QPoint(m_nOffSet+8*m_nD, m_nOffSet+i*m_nD));
    }
    //绘画9条竖线
    for(int i = 0; i <= 8; i++)
    {
        if(i==0 || i==8)
        {
            painter.drawLine(QPoint(m_nOffSet+i*m_nD, m_nOffSet), QPoint(m_nOffSet+i*m_nD, m_nOffSet+9*m_nD));
        }
        else
        {
            painter.drawLine(QPoint(m_nOffSet+i*m_nD, m_nOffSet), QPoint(m_nOffSet+i*m_nD, m_nOffSet+4*m_nD));
            painter.drawLine(QPoint(m_nOffSet+i*m_nD, m_nOffSet+5*m_nD), QPoint(m_nOffSet+i*m_nD, m_nOffSet+9*m_nD));
        }
    }

    //绘画4条斜线
    painter.drawLine(QPoint(m_nOffSet+3*m_nD, m_nOffSet), QPoint(m_nOffSet+5*m_nD, m_nOffSet+2*m_nD));
    painter.drawLine(QPoint(m_nOffSet+3*m_nD, m_nOffSet+2*m_nD), QPoint(m_nOffSet+5*m_nD, m_nOffSet));
    painter.drawLine(QPoint(m_nOffSet+3*m_nD, m_nOffSet+7*m_nD), QPoint(m_nOffSet+5*m_nD, m_nOffSet+9*m_nD));
    painter.drawLine(QPoint(m_nOffSet+3*m_nD, m_nOffSet+9*m_nD), QPoint(m_nOffSet+5*m_nD, m_nOffSet+7*m_nD));

    QRect rect1(m_nOffSet+m_nD,   m_nOffSet+4*m_nD, m_nD, m_nD);
    QRect rect2(m_nOffSet+2*m_nD, m_nOffSet+4*m_nD, m_nD, m_nD);
    QRect rect3(m_nOffSet+5*m_nD, m_nOffSet+4*m_nD, m_nD, m_nD);
    QRect rect4(m_nOffSet+6*m_nD, m_nOffSet+4*m_nD, m_nD, m_nD);
    painter.setFont(QFont("隶书", m_nR, 800));
    painter.drawText(rect1, "楚", QTextOption(Qt::AlignCenter));
    painter.drawText(rect2, "河", QTextOption(Qt::AlignCenter));
    painter.drawText(rect3, "汉", QTextOption(Qt::AlignCenter));
    painter.drawText(rect4, "界", QTextOption(Qt::AlignCenter));
    for(int i = 0; i < piece_buf.length(); i++)
    {
        ChessBoard::drawChessPieces(painter,piece_buf[i]);//绘画单个具体的棋子
        qDebug()<<"paint  "<<piece_buf[i].name;
    }
}
//象棋的棋盘的坐标转换成界面坐标
QPoint ChessBoard::center(int row, int col)
{
    QPoint rePoint;
    //这里注意坐标的转换
    rePoint.ry() = row*m_nD+m_nOffSet;
    rePoint.rx() = col*m_nD+m_nOffSet;

    return rePoint;
}
void ChessBoard::drawChessPieces(QPainter& painter,chess_piece &data)   //绘画单个具体的棋子
{

    QPoint temp = center(data.m_nRow,data.m_nCol);
    QRect rect(temp.x()-m_nR, temp.y()-m_nR, m_nD, m_nD);

    if((data.id&32) == 32)
    {
        painter.setBrush(QBrush(QColor(64,64,196, 80)));
    }
    else if((data.id& 16) == 16)
    {
        painter.setBrush(QBrush(QColor(64,64,196, 10)));
    }
    else
    {
        return;
    }

    painter.setPen(QColor(0, 0, 0));
    painter.drawEllipse(center(data.m_nRow,data.m_nCol), m_nR, m_nR);  //绘画圆形
    painter.setFont(QFont("华文行楷", m_nR, 700));
    if((data.id&32) == 32)
    {
        painter.setPen(QColor(0, 0, 0));
    }
    else if((data.id&16) == 16)
    {
        painter.setPen(QColor(255, 0, 0));
    }
    painter.drawText(rect,data.name, QTextOption(Qt::AlignCenter));  //绘画圆形里面的汉字
}
void ChessBoard::AddShowChessPiece(chess_piece data)
{
    piece_buf.append(data);
}
void ChessBoard::AddShowChessPieces(QVector<chess_piece> data)
{
    for(int i = 0; i < data.length(); i++)
    {
        piece_buf.append(data[i]);
    }
}
