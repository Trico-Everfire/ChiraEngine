#include "BackendGL.h"

#include <cstddef>
#include <map>
#include <stack>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include <vulkan/vulkan.hpp>

#include <core/Assertions.h>
#include <core/Logger.h>

using namespace chira;

CHIRA_CREATE_LOG(VK);

enum class RenderMode {
    CULL_FACE,
    DEPTH_TEST,
    TEXTURE_CUBE_MAP_SEAMLESS,
};

static void changeRenderMode(RenderMode mode, bool enable) {
    // todo(vk)
}

/// State controller to avoid redundant state changes: each state is false by default
std::map<RenderMode, std::stack<bool>> GL_STATES{
        { RenderMode::CULL_FACE, {}, },
        { RenderMode::DEPTH_TEST, {}, },
        { RenderMode::TEXTURE_CUBE_MAP_SEAMLESS, {}, },
};
static void initStates() {
    GL_STATES[RenderMode::CULL_FACE].push(true);
    GL_STATES[RenderMode::DEPTH_TEST].push(true);

    // Wiki says modern hardware is fine with this and it looks better
    GL_STATES[RenderMode::TEXTURE_CUBE_MAP_SEAMLESS].push(true);

    for (const auto& [renderMode, stack] : GL_STATES) {
        changeRenderMode(renderMode, stack.top());
    }
}

static void pushState(RenderMode mode, bool enable) {
    static bool initedStates = false;
    if (!initedStates) {
        initStates();
        initedStates = true;
    }
    runtime_assert(GL_STATES.contains(mode), "This render mode was not added to initStates()!!");
    auto& stack = GL_STATES[mode];
    bool current = stack.top();
    stack.push(enable);
    if (enable != current) {
        changeRenderMode(mode, enable);
    }
}

static void popState(RenderMode mode) {
    if(!GL_STATES.contains(mode) || GL_STATES[mode].size() <= 1) {
        runtime_assert(false, "Attempted to pop render state without a corresponding push!");
    }
    auto& stack = GL_STATES[mode];
    bool old = stack.top();
    stack.pop();
    if (stack.top() != old) {
        changeRenderMode(mode, stack.top());
    }
}

std::string_view Renderer::getHumanName() {
    // todo(vk): return full api version
    return "Vulkan";
}

bool Renderer::setupForDebugging() {
    // todo(vk)
    return true;
}

void Renderer::setClearColor(ColorRGBA color) {
    // todo(vk)
}

[[nodiscard]] static constexpr int getTextureFormatGL(TextureFormat format) {
    // todo(vk)
    return 0;
}

[[nodiscard]] static constexpr int getWrapModeGL(WrapMode mode) {
    // todo(vk)
    return 0;
}

[[nodiscard]] static constexpr int getFilterModeGL(FilterMode mode) {
    // todo(vk)
    return 0;
}

Renderer::TextureHandle Renderer::createTexture2D(const Image& image, WrapMode wrapS, WrapMode wrapT, FilterMode filter,
                                                  bool genMipmaps, TextureUnit activeTextureUnit) {
    TextureHandle handle{};
    // todo(vk)
    return handle;
}

Renderer::TextureHandle Renderer::createTextureCubemap(const Image& imageRT, const Image& imageLT, const Image& imageUP,
                                                       const Image& imageDN, const Image& imageFD, const Image& imageBK,
                                                       WrapMode wrapS, WrapMode wrapT, WrapMode wrapR, FilterMode filter,
                                                       bool genMipmaps, TextureUnit activeTextureUnit) {
    TextureHandle handle{};
    // todo(vk)
    return handle;
}

void Renderer::useTexture(TextureHandle handle, TextureUnit activeTextureUnit) {
    runtime_assert(static_cast<bool>(handle), "Invalid texture handle given to GL renderer!");
    // todo(vk)
}

void* Renderer::getImGuiTextureHandle(Renderer::TextureHandle handle) {
    runtime_assert(handle.type != TextureType::CUBEMAP, "Should probably not be using a cubemap texture in ImGui!");
    return reinterpret_cast<void*>(static_cast<unsigned long long>(handle.handle));
}

void Renderer::destroyTexture(Renderer::TextureHandle handle) {
    runtime_assert(static_cast<bool>(handle), "Invalid texture handle given to GL renderer!");
    // todo(vk)
}

std::stack<Renderer::FrameBufferHandle> GL_FRAMEBUFFERS{};

Renderer::FrameBufferHandle Renderer::createFrameBuffer(int width, int height, WrapMode wrapS, WrapMode wrapT, FilterMode filter, bool hasDepth) {
    FrameBufferHandle handle{ .hasDepth = hasDepth, .width = width, .height = height, };
    // todo(vk)
    return handle;
}

void Renderer::pushFrameBuffer(Renderer::FrameBufferHandle handle) {
    // todo(vk)
}

void Renderer::popFrameBuffer() {
    runtime_assert(!GL_FRAMEBUFFERS.empty(), "Attempted to pop framebuffer without a corresponding push!");
    // todo(vk)
}

void Renderer::useFrameBufferTexture(Renderer::FrameBufferHandle handle, TextureUnit activeTextureUnit) {
    // todo(vk)
}

void* Renderer::getImGuiFrameBufferHandle(Renderer::FrameBufferHandle handle) {
    return reinterpret_cast<void*>(static_cast<unsigned long long>(handle.colorHandle));
}

void Renderer::destroyFrameBuffer(Renderer::FrameBufferHandle handle) {
    if (!handle) {
        return;
    }
    // todo(vk)
}

int Renderer::getFrameBufferWidth(Renderer::FrameBufferHandle handle) {
    return handle.width;
}

int Renderer::getFrameBufferHeight(Renderer::FrameBufferHandle handle) {
    return handle.height;
}

void Renderer::recreateFrameBuffer(Renderer::FrameBufferHandle* handle, int width, int height, WrapMode wrapS, WrapMode wrapT, FilterMode filter, bool hasDepth) {
    if (!handle)
        return;
    if (*handle) {
        destroyFrameBuffer(*handle);
        *handle = Renderer::createFrameBuffer(width, height, wrapS, wrapT, filter, hasDepth);
    } else {
        // This is the window framebuffer, just resize it
        handle->width = width;
        handle->height = height;
    }
}

[[nodiscard]] static constexpr int getShaderModuleTypeGL(ShaderModuleType type) {
    // todo(vk)
    return 0;
}

[[nodiscard]] static Renderer::ShaderModuleHandle createShaderModule(std::string_view shader, Renderer::ShaderHandle shaderHandle, ShaderModuleType type) {
    Renderer::ShaderModuleHandle handle{};
    // todo(vk)
    return handle;
}

static void destroyShaderModule(Renderer::ShaderModuleHandle handle) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader module handle given to GL renderer!");
    // todo(vk)
}

Renderer::ShaderHandle Renderer::createShader(std::string_view vertex, std::string_view fragment) {
    ShaderHandle handle{};
    // todo(vk)
    return handle;
}

void Renderer::useShader(Renderer::ShaderHandle handle) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::destroyShader(Renderer::ShaderHandle handle) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    destroyShaderModule(handle.vertex);
    destroyShaderModule(handle.fragment);
    // todo(vk)
}

void Renderer::setShaderUniform1b(Renderer::ShaderHandle handle, std::string_view name, bool value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform1u(Renderer::ShaderHandle handle, std::string_view name, unsigned int value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform1i(Renderer::ShaderHandle handle, std::string_view name, int value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform1f(Renderer::ShaderHandle handle, std::string_view name, float value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform2b(Renderer::ShaderHandle handle, std::string_view name, glm::vec2b value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform2u(Renderer::ShaderHandle handle, std::string_view name, glm::vec2u value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform2i(Renderer::ShaderHandle handle, std::string_view name, glm::vec2i value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform2f(Renderer::ShaderHandle handle, std::string_view name, glm::vec2f value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform3b(Renderer::ShaderHandle handle, std::string_view name, glm::vec3b value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform3u(Renderer::ShaderHandle handle, std::string_view name, glm::vec3u value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform3i(Renderer::ShaderHandle handle, std::string_view name, glm::vec3i value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform3f(Renderer::ShaderHandle handle, std::string_view name, glm::vec3f value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform4b(Renderer::ShaderHandle handle, std::string_view name, glm::vec4b value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform4u(Renderer::ShaderHandle handle, std::string_view name, glm::vec4u value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform4i(Renderer::ShaderHandle handle, std::string_view name, glm::vec4i value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform4f(Renderer::ShaderHandle handle, std::string_view name, glm::vec4f value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

void Renderer::setShaderUniform4m(Renderer::ShaderHandle handle, std::string_view name, glm::mat4 value) {
    runtime_assert(static_cast<bool>(handle), "Invalid shader handle given to GL renderer!");
    // todo(vk)
}

Renderer::UniformBufferHandle Renderer::createUniformBuffer(std::ptrdiff_t size) {
    UniformBufferHandle handle{};
    // todo(vk)
    return handle;
}

void Renderer::bindUniformBufferToShader(Renderer::ShaderHandle shaderHandle, Renderer::UniformBufferHandle uniformBufferHandle, std::string_view name) {
    runtime_assert(static_cast<bool>(shaderHandle), "Invalid shader handle given to GL renderer!");
    runtime_assert(static_cast<bool>(uniformBufferHandle), "Invalid uniform buffer handle given to GL renderer!");
    // todo(vk)
}

void Renderer::updateUniformBuffer(Renderer::UniformBufferHandle handle, const void* buffer, std::ptrdiff_t length) {
    runtime_assert(static_cast<bool>(handle), "Invalid uniform buffer handle given to GL renderer!");
    // todo(vk)
}

void Renderer::updateUniformBufferPart(Renderer::UniformBufferHandle handle, std::ptrdiff_t start, const void* buffer, std::ptrdiff_t length) {
    runtime_assert(static_cast<bool>(handle), "Invalid uniform buffer handle given to GL renderer!");
    // todo(vk)
}

void Renderer::destroyUniformBuffer(Renderer::UniformBufferHandle handle) {
    runtime_assert(static_cast<bool>(handle), "Invalid uniform buffer handle given to GL renderer!");
    // todo(vk)
}

[[nodiscard]] static constexpr int getMeshDrawModeGL(MeshDrawMode mode) {
    // todo(vk)
    return 0;
}

[[nodiscard]] static constexpr int getMeshDepthFunctionGL(MeshDepthFunction function) {
    // todo(vk)
    return 0;
}

[[nodiscard]] static constexpr int getMeshCullTypeGL(MeshCullType type) {
    // todo(vk)
    return 0;
}

Renderer::MeshHandle Renderer::createMesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, MeshDrawMode drawMode) {
    MeshHandle handle{ .numIndices = static_cast<int>(indices.size()) };
    // todo(vk)
    return handle;
}

void Renderer::updateMesh(MeshHandle* handle, const std::vector<Vertex>& vertices, const std::vector<Index>& indices, MeshDrawMode drawMode) {
    runtime_assert(static_cast<bool>(*handle), "Invalid mesh handle given to GL renderer!");
    // todo(vk)
}

void Renderer::drawMesh(MeshHandle handle, MeshDepthFunction depthFunction, MeshCullType cullType) {
    runtime_assert(static_cast<bool>(handle), "Invalid mesh handle given to GL renderer!");
    // todo(vk)
}

void Renderer::destroyMesh(MeshHandle handle) {
    runtime_assert(static_cast<bool>(handle), "Invalid mesh handle given to GL renderer!");
    // todo(vk)
}
