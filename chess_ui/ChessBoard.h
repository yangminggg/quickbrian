#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QMainWindow>
#include <QFrame>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QtGlobal>
#include <QVector>
#include "chess_core/chess_piece.h"

namespace Ui {
class ChessBoard;
}

class ChessBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = 0);
    ~ChessBoard();
public:
    //视图相关
    virtual void paintEvent(QPaintEvent *);      //绘画棋盘
    QPoint center(int row, int col);//象棋的棋盘的坐标转换成界面坐标
    void drawChessPieces(QPainter& painter,chess_piece &data);//绘画单个具体的棋子
public:
    int m_nR;          //棋子半径
    int m_nOffSet;     //距离界面的边距
    int m_nD;          //间距为50px
    QVector<chess_piece> piece_buf;
public:
    void AddShowChessPiece(chess_piece data);
    void AddShowChessPieces(QVector<chess_piece> data);
private:
    Ui::ChessBoard *ui;
};

#endif // CHESSBOARD_H
