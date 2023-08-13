#pragma once

#include <iostream>
#include <vector>
#include <variant>
#include <tuple>
#include <format>

namespace NonVirtual {

template <typename T>
concept IsSystem = requires(T System) {
    {
        System.Update()
    } -> std::same_as<void>;
};

template <typename T, typename... U>
concept IsOneOf = (... or std::is_same_v<T, U>);

class ISystem
{
protected:
    std::string Name;
};
class FAudioSystem : public ISystem
{
public:
    FAudioSystem(const std::string& InName = {}) { Name = InName; };
    void Update()
    {
        std::cout << std::format("AudioSystem {} : Update NonVirtual\n", Name);
    }
};
class FInputSystem : public ISystem
{
public:
    FInputSystem(const std::string& InName = {}) { Name = InName; };
    void Update()
    {
        std::cout << std::format("InputSystem {} : Update NonVirtual\n", Name);
    }
};

template <IsSystem... SystemTypes>
class FSystemManagerVariant
{
public:
    template <IsOneOf<SystemTypes...> T>
    void RegisterSystem(T&& System)
    {
        Systems.push_back(std::move(System));
    }

    void Update()
    {
        for (auto& System : Systems)
        {
            std::visit([](auto System) { System.Update(); }, System);
        }
    }

    static FSystemManagerVariant& Get()
    {
        static FSystemManagerVariant Manager;
        return Manager;
    }

private:
    FSystemManagerVariant()
    {
        RegisterSystem(FInputSystem());
        RegisterSystem(FAudioSystem());
    }

    std::vector<std::variant<SystemTypes...>> Systems;
};

template <IsSystem... SystemTypes>
class FSystemManagerTupleVector
{
public:
    template <IsOneOf<SystemTypes...> T>
    void RegisterSystem(T&& System)
    {
        std::get<std::vector<T>>(Systems).push_back(std::move(System));
    }

    void Update()
    {
        std::apply(
            [this](auto&... SingleTypeSystems) {
                (UpdateSystem(SingleTypeSystems), ...);
            },
            Systems);
    }

    static FSystemManagerTupleVector& Get()
    {
        static FSystemManagerTupleVector Manager;
        return Manager;
    }

private:
    FSystemManagerTupleVector()
    {
        RegisterSystem(FInputSystem());
        RegisterSystem(FAudioSystem());
    }

    using SystemList = std::tuple<std::vector<SystemTypes>...>;
    SystemList Systems{};

    void UpdateSystem(auto& SingleTypeSystems)
    {
        for (auto& System : SingleTypeSystems)
        {
            System.Update();
        }
    }
};
} // namespace NonVirtual