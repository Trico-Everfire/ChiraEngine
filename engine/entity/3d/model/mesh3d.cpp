#include "mesh3d.h"

#include <utility/math/matrix.h>

using namespace chira;

void Mesh3d::render(const glm::mat4& parentTransform) {
    this->mesh->render(transformToMatrix(parentTransform, this->position, this->rotation));
    Entity3d::render(parentTransform);
}

glm::vec3 Mesh3d::getAABB() const {
    return {}; // todo: get aabb from mesh
}
