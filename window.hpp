#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <random>

#include "abcgOpenGL.hpp"

#include "paddle.hpp"
#include "ball.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onEvent(SDL_Event const &event) override;
  void onCreate() override;
  void onUpdate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;

private:
  glm::ivec2 m_viewportSize{};

  GLuint m_objectsProgram{};

  GameData m_gameData;

  Paddle m_player;
  Ball m_ball;

  abcg::Timer m_restartWaitTimer;

  ImFont *m_font{};

  std::default_random_engine m_randomEngine;

  void restart();
};

#endif