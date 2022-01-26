#pragma once

#include <functional>
#include <string>
#include <resource/propertiesResource.h>
#include <render/shader.h>

namespace chira {
    class MaterialBase : public PropertiesResource {
    public:
        explicit MaterialBase(const std::string& identifier_);
        void compile(const nlohmann::json& properties) override;
        virtual void use() const;
        [[nodiscard]] SharedPointer<Shader> getShader() const;
    protected:
        SharedPointer<Shader> shader;
    };

    class MaterialFactory {
        using factoryFunction = std::function<SharedPointer<MaterialBase>(const std::string&)>;
    public:
        MaterialFactory() = delete;
        static bool registerMaterialType(const std::string& name, factoryFunction createFunc);
        static const factoryFunction& getMaterialType(const std::string& name);
    private:
        static std::unordered_map<std::string, factoryFunction>& getFactoryMethods();
    };
}

#define CHIRA_REGISTER_MATERIAL_TYPE(ResourceClassName)                                        \
    static inline const bool ResourceClassName##FactoryRegistryHelper =                        \
    chira::MaterialFactory::registerMaterialType(                                              \
        #ResourceClassName,                                                                    \
        [](const std::string& identifier) -> chira::SharedPointer<chira::MaterialBase> {       \
            return chira::Resource::getResource<ResourceClassName>(identifier)                 \
                   .castAssert<chira::MaterialBase>();                                         \
        }                                                                                      \
    )

#define CHIRA_GET_MATERIAL(type, identifier) \
    chira::MaterialFactory::getMaterialType(type)(identifier).castAssert<chira::MaterialBase>()
