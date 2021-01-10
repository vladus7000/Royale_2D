#include "Character.hpp"

USING_NS_CC;

Character::Character()
{
    m_sprite = Sprite::create();
    m_sprite->retain();
    setState(m_state);
}

Character::~Character()
{
    if (m_sprite)
    {
        m_sprite->release();
    }
}

void Character::setState(State s)
{
    m_state = s;

    switch (s)
    {
    case Character::State::Parachuting:
        m_sprite->setTexture("parachuting.png");
        m_sprite->setScale(0.5f);
        break;
    case Character::State::OnGround:
        m_sprite->setTexture("Top_Down_Survivor/knife/idle/survivor-idle_knife_0.png");
        m_sprite->setScale(0.3f);
        break;
    default:
        break;
    }
}

void Character::update(float delta)
{
}

void Character::setInput()
{
}
