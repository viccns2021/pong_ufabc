#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include <bitset>

enum class Input { Right, Left, Down, Up, Fire };
enum class State { Playing, GameOver, Win };

struct GameData {
  State m_state{State::Playing};
  std::bitset<5> m_input;  // [up, down]
  float ball_dx = -0.35f;
  float ball_dy = -0.27f;
  int ct = 0;
};

#endif