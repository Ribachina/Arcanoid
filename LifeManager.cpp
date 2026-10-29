#include "LifeManager.hpp"
#include <utility>

int LifeManager::GetLives() const
{
    return m_lives;
}

void LifeManager::LoseLife()
{
    if (m_lives > 0)
    {
        --m_lives;
    }
}

void LifeManager::Save(std::unique_ptr<GameMemento> memento)
{
    m_lastMemento = std::move(memento);
}

const GameMemento* LifeManager::GetLastMemento() const
{
    return m_lastMemento.get();
}
