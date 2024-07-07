#ifndef S0_REDUCE_FACTORY_REGISTRY_HPP
#define S0_REDUCE_FACTORY_REGISTRY_HPP

#include "s0_general_reduce_interface.hpp"

#include <unordered_map>
#include <functional>
#include <memory>

class ReduceFactoryRegistry
{
public:
    using FactoryFunction = std::function<std::unique_ptr<s0m4b0dY::GeneralReduceInterface>()>;

    static ReduceFactoryRegistry& instance()
    {
        static ReduceFactoryRegistry instance;
        return instance;
    }

    void registerFactory(const std::string& typeName, FactoryFunction factory)
    {
        factoryMap_[typeName] = factory;
    }

    std::vector<std::unique_ptr<s0m4b0dY::GeneralReduceInterface>> createAll() const
    {
        std::vector<std::unique_ptr<s0m4b0dY::GeneralReduceInterface>> implementations;
        for (const auto& pair : factoryMap_)
        {
            implementations.push_back(pair.second());
        }
        return implementations;
    }

private:
    std::unordered_map<std::string, FactoryFunction> factoryMap_;

    ReduceFactoryRegistry() = default;
    ~ReduceFactoryRegistry() = default;
    ReduceFactoryRegistry(const ReduceFactoryRegistry&) = delete;
    ReduceFactoryRegistry& operator=(const ReduceFactoryRegistry&) = delete;
};

#define S0M4B0DY_REGISTER_REDUCE_IMPLEMENTATION(typeName, className) \
    namespace { \
        const bool registered_##className = []() { \
            ReduceFactoryRegistry::instance().registerFactory(typeName, []() { \
                return std::make_unique<className>(); \
            }); \
            return true; \
        }(); \
    }

#endif
