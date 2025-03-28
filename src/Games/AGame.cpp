#include "AGame.hpp"

void arcade::game::AGame::init()
{
}

void arcade::game::AGame::update(const std::pair<types::Position, types::InputEvent>)
{
}

void arcade::game::AGame::stop()
{
}

const std::string &arcade::game::AGame::getName() const
{
    return this->_name;
}

const arcade::game::IGame::Entities &arcade::game::AGame::getEntities() const
{
    return this->_entities;
}

int arcade::game::AGame::getScore() const
{
    return this->_score;
}

bool arcade::game::AGame::isGameOver() const
{
    return this->_gameOver;
}

void arcade::game::AGame::setGameOver(bool state)
{
    this->_gameOver = state;
}

void arcade::game::AGame::addEntity(types::EntityType type, types::EntityDraw draw,
    types::Position pos, char c, uint32_t color, const std::string str)
{
    types::Entity entity = {type, pos, c, color};

    this->_entities[draw].push_back(entity);
    this->_entitiesIndex[pos] = &this->_entities[draw].back();
}

void arcade::game::AGame::removeEntityAt(const types::Position &pos)
{
    const auto it = this->_entitiesIndex.find(pos);

    if (it != this->_entitiesIndex.end()) {
        for (auto &[draw, vect] : this->_entities) {
            for (auto vect_it = vect.begin(); vect_it != vect.end(); ++vect_it) {
                if (&(*vect_it) == it->second) {
                    vect.erase(vect_it);
                    this->_entitiesIndex.erase(it);
                    return;
                }
            }
        }
        this->_entitiesIndex.erase(it);
    }
}

arcade::types::Entity *arcade::game::AGame::getEntityAt(const types::Position &pos)
{
    const auto it = this->_entitiesIndex.find(pos);

    if (it != this->_entitiesIndex.end())
        return it->second;
    return nullptr;
}

void arcade::game::AGame::clearEntities()
{
    this->_entities.clear();
}
