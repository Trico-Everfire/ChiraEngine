#pragma once

#include <string>
#include <vector>
#include <loader/mesh/IMeshLoader.h>
#include <render/backend/RenderTypes.h>
#include <render/material/MaterialFactory.h>

namespace chira {

class MeshData {
public:
    MeshData() = default;
    void render(glm::mat4 model);
    virtual ~MeshData();
    [[nodiscard]] SharedPointer<IMaterial> getMaterial() const;
    void setMaterial(SharedPointer<IMaterial> newMaterial);
    [[nodiscard]] MeshDepthFunction getDepthFunction() const;
    void setDepthFunction(MeshDepthFunction function);
    [[nodiscard]] MeshCullType getCullType() const;
    void setCullType(MeshCullType type);
    [[nodiscard]] std::vector<byte> getMeshData(const std::string& meshLoader) const;
    void appendMeshData(const std::string& loader, const std::string& identifier);
protected:
    bool initialized = false;
    Renderer::MeshHandle handle{};
    MeshDrawMode drawMode = MeshDrawMode::STATIC;
    MeshDepthFunction depthFunction = MeshDepthFunction::LEQUAL;
    MeshCullType cullType = MeshCullType::BACK;
    SharedPointer<IMaterial> material;
    std::vector<Vertex> vertices;
    std::vector<Index> indices;
    /// Establishes the vertex buffers and copies the current mesh data into them.
    void setupForRendering();
    /// Updates the vertex buffers with the current mesh data.
    void updateMeshData();
    /// Does not call updateMeshData().
    void clearMeshData();
};

} // namespace chira
