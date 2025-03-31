#include "widget.h"
#include <QApplication>
#include "Eigen/Dense"
#include <unsupported/Eigen/FFT>
#include "chess_ui/ChessBoard.h"
#include "chess_core/fen_tool.h"
#include "chess_core/chess_piece.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    Eigen::FFT<double> fft;
    ChessBoard b;
    b.AddShowChessPiece(chess_piece::BuildChessPiece(chess_piece::JIANG,16,0,4,1));
    b.show();

    FEN_TOOL::test();

    return a.exec();
}
