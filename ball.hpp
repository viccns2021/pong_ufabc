#ifndef BALL_HPP_
#define BALL_HPP_

#include "abcgOpenGL.hpp"

#include "gamedata.hpp"

class Ball {
public:
  void create(GLuint program);
  void paint(GameData gameData);
  void destroy();
  void update(GameData& gameData, float deltaTime);

  glm::vec4 m_color{1};
  float m_rotation{0.2f};
  float m_scale{0.15f};
  glm::vec2 m_translation{};
  glm::vec2 m_velocity{};

  abcg::Timer m_trailBlinkTimer;
  abcg::Timer m_bulletCoolDownTimer;

private:
  GLuint m_program{};
  GLint m_translationLoc{};
  GLint m_colorLoc{};
  GLint m_scaleLoc{};
  GLint m_rotationLoc{};

  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};
};
#endif