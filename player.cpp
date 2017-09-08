#include "player.h"
#include <QDebug>

Player::Player(QString name, QString color)// : QObject(0)
{
    this->m_name = name;
    this->m_dice = "<b>Dice:</b>";
    this->m_positionLabel = "<b>Position:</b> ";
    this->m_position = 0;
    this->m_posLabel = new QLabel("0");
    this->m_posLabel->setStyleSheet("font-weight: bold; color: " + color);
    this->m_diceLabel = new QLabel("0");
    this->m_diceLabel->setStyleSheet("font-weight: bold; color: " + color);
    this->m_Start = true;
    this->m_color = color;
}

// GETTERS

QLabel *Player::getPlayerPositionLabel()
{
    return this->m_posLabel;
}

QString *Player::getName()
{
    return &this->m_name;
}

QString *Player::getDice()
{
    return &this->m_dice;
}

QString *Player::getPositionLabel()
{
    return &this->m_positionLabel;
}

QLabel *Player::getDiceLabel()
{
    return this->m_diceLabel;
}

int Player::getPosition()
{
    return this->m_position;
}

bool Player::getStart()
{
    return this->m_Start;
}

QString *Player::getColor()
{
    return &this->m_color;
}

// SETTERS

void Player::setPlayerPositionLabel(int position)
{
    qDebug()<<"Position:"<<position;
    this->m_posLabel->setNum(position);
    qDebug()<<"Label:"<<this->m_posLabel->text();
}

void Player::setDiceLabel(int diceValue)
{
    this->m_diceLabel->setNum(diceValue);
}

void Player::setPosition(int position)
{
    this->m_position = position;
}

void Player::setStart(bool start)
{
    this->m_Start = start;
}
