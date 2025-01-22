#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <set>
#include <vector>


class Player {
public:
    Player(std::string id) : m_id(id) {} 

    std::string getId() {  
        return m_id;
    }

protected:
    std::string m_id;         // 玩家ID

};

#endif // PLAYER_H
