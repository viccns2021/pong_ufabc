#include "ball.hpp"

#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/rotate_vector.hpp>

void Ball::create(GLuint program) {
  destroy();

  m_program = program;

  // Get location of uniforms in the program
  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
  m_rotationLoc = abcg::glGetUniformLocation(m_program, "rotation");
  m_scaleLoc = abcg::glGetUniformLocation(m_program, "scale");
  m_translationLoc = abcg::glGetUniformLocation(m_program, "translation");

  // Reset paddle attributes
  m_rotation = 0.0f;
  m_translation = glm::vec2(-0.0f, 0.0f);
  m_velocity = glm::vec2(0);

  // clang-format off
  std::array positions{
      glm::vec2{ 0.0f,  0.5f},       // Top
      glm::vec2{-0.4755f,  0.1545f}, // Top-left
      glm::vec2{-0.2939f, -0.4045f}, // Bottom-left
      glm::vec2{ 0.2939f, -0.4045f}, // Bottom-right
      glm::vec2{ 0.4755f,  0.1545f}  // Top-right
  };

  std::array const indices{0, 1, 2, 0, 2, 3, 0, 3, 4}; // Vertex indices to create a pentagon



  // clang-format on                           

  // Generate VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Generate EBO
  abcg::glGenBuffers(1, &m_EBO);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  GLint positionAttribute{abcg::glGetAttribLocation(m_program, "inPosition")};

  // Create VAO
  abcg::glGenVertexArrays(1, &m_VAO);

  // Bind vertex attributes to current VAO
  abcg::glBindVertexArray(m_VAO);

  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);
}

void Ball::paint(GameData gameData) {
  if (gameData.m_state != State::Playing) return;

  abcg::glUseProgram(m_program);

  abcg::glBindVertexArray(m_VAO);

  abcg::glUniform1f(m_scaleLoc, m_scale);
  abcg::glUniform1f(m_rotationLoc, m_rotation);
  abcg::glUniform2fv(m_translationLoc, 1, &m_translation.x);

  abcg::glUniform4fv(m_colorLoc, 1, &m_color.r);
  abcg::glDrawElements(GL_TRIANGLES, 3 * 3, GL_UNSIGNED_INT, nullptr);

  abcg::glBindVertexArray(0);

  abcg::glUseProgram(0);
}

void Ball::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteBuffers(1, &m_EBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}

void Ball::update(GameData& gameData, float deltaTime) {
  // Apply thrust
  m_rotation = glm::wrapAngle(m_rotation + 4.0f * deltaTime);
  m_translation += glm::vec2{
   gameData.ball_dx * deltaTime,
   gameData.ball_dy * deltaTime};

  if(m_translation.x < -1.0f || m_translation.x > 1.0f){
    gameData.ball_dx = -1.0f * gameData.ball_dx;
    m_translation.x += gameData.ball_dx * deltaTime;
    gameData.ct +=1;
  }

  if(m_translation.y < -1.0f || m_translation.y > 1.0f){
    gameData.ball_dy = -1.0f * gameData.ball_dy;
    m_translation.y += gameData.ball_dy * deltaTime;
    gameData.ct +=1;
  }

}