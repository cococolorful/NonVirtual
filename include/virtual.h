#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <format>

namespace Virtual {

class ISystem
{
public:
    virtual void Update() = 0;

protected:
    std::string Name;
};
class FAudioSystem : public ISystem
{
public:
    FAudioSystem(const std::string& InName = {}) { Name = InName; };
    void Update() override
    {
        std::cout << std::format("AudioSystem {} : Update Virtual\n", Name);
    }
};
class FInputSystem : public ISystem
{
public:
    FInputSystem(const std::string& InName = {}) { Name = InName; };
    void Update() override
    {
        std::cout << std::format("InputSystem {} : Update Virtual\n", Name);
    }
};

class FSystemManager
{
public:
    void RegisterSystem(std::unique_ptr<ISystem> System)
    {
        Systems.push_back(std::move(System));
    }

    void Update()
    {
        for (auto& System : Systems)
        {
            System->Update();
        }
    }

    static FSystemManager& Get()
    {
        static FSystemManager Manager;
        return Manager;
    }

private:
    FSystemManager()
    {
        RegisterSystem(std::make_unique<FInputSystem>());
        RegisterSystem(std::make_unique<FAudioSystem>());
    }

    std::vector<std::unique_ptr<ISystem>> Systems;
};
} // namespace Virtual