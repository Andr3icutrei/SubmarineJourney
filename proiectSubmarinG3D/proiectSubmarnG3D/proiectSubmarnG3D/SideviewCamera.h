#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "ICamera.h"
#include <GL/glew.h>

class SideviewCamera : public ICamera
{
private:
    glm::vec3 m_position;
    glm::vec3 m_target;
    glm::vec3 m_worldUp;

    const float m_fov;
    const float m_aspectRatio;
    const float m_nearPlane;
    const float m_farPlane;

    glm::mat4 m_projectionMatrix;

    int m_width;
    int m_height;
public:
    SideviewCamera(glm::vec3 pos, glm::vec3 target, glm::vec3 worldUp,const int width,const int height);
    SideviewCamera& operator=(const SideviewCamera& other);
    void setPosition(glm::vec3 pos) { m_position = pos; }
    void setTarget(glm::vec3 target) { m_target = target; }
    void setWorldUp(glm::vec3 worldUp) { m_worldUp = worldUp; }

    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getTarget() const { return m_target; }
    glm::vec3 getWorldUp() const { return m_worldUp; }
    void Reshape(int windowWidth, int windowHeight) override;

    glm::mat4 getViewMatrix() const override{
        return glm::lookAt(m_position, m_target ,m_worldUp);
    }
    glm::mat4 getProjectionMatrix() const override {
        return m_projectionMatrix;
    }
};

