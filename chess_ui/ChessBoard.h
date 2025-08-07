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
#include "chess_core/chess_board_define.h"

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
    virtual void mouseReleaseEvent(QMouseEvent *ev); //鼠标释放事件，捕捉棋子
    QPoint center(int row, int col);//象棋的棋盘的坐标转换成界面坐标
    void drawChessPieces(QPainter& painter,chess_piece &data);//绘画单个具体的棋子
    QPoint getRealPoint(QPoint pt);
    void click(QPoint pt);
    bool isChecked(QPoint pt, int &row, int &col);//检查是否在棋子中心,通过棋子中心坐标判断鼠标点距离来判断，返回棋子所在的行列
    int CherkPieceInBoard(int row, int col);//判断棋子是否在棋局上,获取棋子ID，-1是无效值
    void clickPieces(int id, int row, int col);//点击棋子响应，选中，吃子
    void trySelectStone(int id);    //尝试选中棋

public:
    int m_nR;          //棋子半径
    int m_nOffSet;     //距离界面的边距
    int m_nD;          //间距为50px
    std_chess_board_pos ui_chess_board_pos;//界面的局面,保存界面的视图局面
    QVector<chess_piece> piece_buf;//界面的棋子,保存界面的棋子
public:
    void AddShowChessPiece(chess_piece data);
    void AddShowChessPieces(QVector<chess_piece> data);
private:
    Ui::ChessBoard *ui;
};

#endif // CHESSBOARD_H
