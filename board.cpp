#include <stdlib.h>
#include "board.h"

Board::Board(QWidget *parent) :
    QWidget(parent)
{
    srand (time(NULL));

    this->m_button = new QPushButton("Play", this);
    this->m_dice = 0;
    this->m_currentPlayer = 0;
    this->m_casesList = QList<QPushButton *>();
    this->m_playersList = QList<Player *>();
    this->m_layout = new QGridLayout(this);
    this->m_colors<<"Blue"<<"red"<<"lime"<<"pink";

    this->setWindowTitle("Jeu de l'oie");
    bool ok;
    int nPlayers = QInputDialog::getInt(this, "Number of players", "Choose", 2, 2, 4, 1, &ok);
    if(!ok)
        exit(-1);

    // Players

    for(int i=0; i<nPlayers; i++)
    {
        Player *tmp = new Player(QString("<b>Player ")+QString::number(i+1)+"</b>", this->m_colors[i]);
        this->m_playersList.append(tmp);

        QLabel *nameLabel = new QLabel(*(tmp->getName()));
        QLabel *diceLabel = new QLabel(*(tmp->getDice()));
        QLabel *positionLabel = new QLabel(*(tmp->getPositionLabel()));

        nameLabel->setStyleSheet("color: " + this->m_colors[i]);
        diceLabel->setStyleSheet("color: " + this->m_colors[i]);
        positionLabel->setStyleSheet("color: " + this->m_colors[i]);

        this->m_layout->addWidget(nameLabel, 1, 4*i, 1, 2);
        this->m_layout->addWidget(diceLabel, 2, i*4, 1, 1);
        this->m_layout->addWidget(positionLabel, 2, i*4+2, 1, 1);
        this->m_layout->addWidget(tmp->getDiceLabel(), 2, i*4+1);
        this->m_layout->addWidget(tmp->getPlayerPositionLabel(), 2, i*4+3, 1, 1);
    }

    this->m_layout->addWidget(this->m_button, 0, 0);

    // Buttons

    for(int i=0; i<64; i++)
    {
        QPushButton *tmp = new QPushButton(QString::number(i), this);
        tmp->setStyleSheet("background-color: transparent");
        this->m_casesList.append(tmp);
        this->m_layout->addWidget(tmp, (i/9)+3, (i%9));
    }

    this->setLayout(this->m_layout);

    connect(this->m_button, SIGNAL(clicked()), this, SLOT(play()));
}

void Board::play()
{
    Player *currentPlayer = this->m_playersList[this->m_currentPlayer];
    this->m_dice = rand() % 10 + 2;
    int tmpPosition = currentPlayer->getPosition();

    if (currentPlayer->getPosition() + this->m_dice > 63)
        goTo(currentPlayer, 63 - ((currentPlayer->getPosition() + this->m_dice) - 63));
    else
    {
        move(currentPlayer, this->m_dice);
        currentPlayer->setStart(false);
    }

    foreach (Player *p, this->m_playersList)
    {
        if(p->getName() != currentPlayer->getName() && p->getPosition() == currentPlayer->getPosition())
        {
            goTo(p, tmpPosition, true);
            return;
        }
    }

    if (currentPlayer->getStart())
    {
        if (currentPlayer->getPosition() == 6)
            goTo(currentPlayer, 12);
        else if (currentPlayer->getPosition() == 9)
            goTo(currentPlayer, 26);
    }
    else
    {
        if (currentPlayer->getPosition() == 42)
            goTo(currentPlayer, 30);
        else if (currentPlayer->getPosition() == 58)
            goTo(currentPlayer, 0);
        else if (currentPlayer->getPosition() == 63)
            winner(currentPlayer);
    }

    if(this->m_currentPlayer == this->m_playersList.length()-1)
        this->m_currentPlayer=0;
    else
        this->m_currentPlayer++;

}

void Board::winner(Player *player)
{
    this->m_button->setDisabled(true);
    QMessageBox::information(this, "Winner !", QString("<font color='") + *player->getColor() + "'>" + *player->getName() + " wins ! </font>");
}

void Board::move(Player *player, int nbCases)
{
    this->goTo(player, player->getPosition() + nbCases);
    player->getDiceLabel()->setNum(nbCases);

//    if(this->m_position == 63)
//        emit this->winning(this->m_name);
}

void Board::goTo(Player *player, int numCase, bool sameCase)
{
    if (!sameCase)
        this->m_casesList[player->getPosition()]->setStyleSheet("background-color: transparent");

    player->setPlayerPositionLabel(numCase);
    player->setPosition(numCase);
    this->m_casesList[player->getPosition()]->setStyleSheet(QString("background-color: ") + *player->getColor());
}
