//
//  Camera.cpp
//  Lab5
//
//  Created by CGIS on 28/10/2016.
//  Copyright © 2016 CGIS. All rights reserved.
//
#include "Camera.hpp"

namespace gps {
    
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget)
    {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f)));

		//
		//this->cameraUp = glm::normalize(this->cameraDirection +  glm::vec3(0.0f, 1.0f, 0.0f));
		this->cameraUp = glm::cross(cameraDirection, cameraRightDirection);
    }
    
    glm::mat4 Camera::getViewMatrix()
    {
        return glm::lookAt(cameraPosition, cameraPosition + cameraDirection , glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void Camera::move(MOVE_DIRECTION direction, float speed)
    {
		glm::vec3 strafeDirection = glm::cross(cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f));
        switch (direction) {
            case MOVE_FORWARD:
                cameraPosition += cameraDirection * speed;
                break;
                
            case MOVE_BACKWARD:
                cameraPosition -= cameraDirection * speed;
                break;
                
            case MOVE_RIGHT:
                ///cameraPosition += cameraRightDirection * speed;
				cameraPosition += strafeDirection * speed;
                break;
                
            case MOVE_LEFT:
                ///cameraPosition -= cameraRightDirection * speed;
				cameraPosition += -strafeDirection * speed;
                break;

			case MOVE_UP:
				//cameraPosition += cameraUp * speed - cameraDirection * speed;
				cameraPosition -= cameraUp * speed;
				break;

			case MOVE_DOWN:
				//cameraPosition -= cameraUp * speed - cameraDirection * speed;
				cameraPosition += cameraUp * speed;
				break;

			case ROTATE_RIGHT:
				cameraDirection = glm::mat3(glm::rotate(-0.1f * speed, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraDirection;
				break;

			case ROTATE_LEFT:
				cameraDirection = glm::mat3(glm::rotate(0.1f * speed, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraDirection;
				break;
        }
    }
    

    void Camera::rotate(float pitch, float yaw)
    {

    }
    
}
