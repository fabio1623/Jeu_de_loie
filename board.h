#ifndef BOARD_H
#define BOARD_H

#include <QtWidgets>
#include "player.h"

class Board : public QWidget
{
    Q_OBJECT

private:
    QPushButton             *m_button;
    QGridLayout             *m_layout;
    QStringList              m_colors;
    QList<Player *>          m_playersList;
    QList<QPushButton *>     m_casesList;
    int                      m_dice;
    int                      m_currentPlayer;
public:
    Board(QWidget *parent = 0);
    void           move(Player *player, int nbCases);
    void           goTo(Player *player, int numCase, bool sameCase = false);
signals:
    
public slots:
    void                     play();
    void                     winner(Player *player);
};

#endif // BOARD_H
