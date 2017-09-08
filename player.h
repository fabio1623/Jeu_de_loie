#ifndef PLAYER_H
#define PLAYER_H

#include <QtWidgets>

class Player// : public QObject
{
    //Q_OBJECT
private:
    QLabel      *m_posLabel;
    QLabel      *m_diceLabel;
    QString      m_name;
    QString      m_dice;
    QString      m_positionLabel;
    QString      m_color;
    int          m_position;
    bool         m_Start;
public:
    Player(QString name, QString color);

    QLabel      *getPlayerPositionLabel();
    QString     *getName();
    QString     *getDice();
    QString     *getColor();
    QString     *getPositionLabel();
    QLabel      *getDiceLabel();
    int          getPosition();
    bool         getStart();

    void         setPlayerPositionLabel(int position);
    void         setDiceLabel(int diceValue);
    void         setPosition(int position);
    void         setStart(bool start);
/*
    void         move(int nbCases);
    void         goTo(int numCase);
*/
signals:
//    void         winning(QString playerName);
};

#endif // PLAYER_H
