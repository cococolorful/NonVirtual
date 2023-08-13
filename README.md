# Using Modern C++ to Eliminate Virtual Functions

**Practices** of [ Using Modern C++ to Eliminate Virtual Functions](https://www.youtube.com/watch?v=gTNJXVmuRRA)


```cpp
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
// main.cpp
auto& System = FSystemManagerTupleVector<
    FInputSystem, FAudioSystem>::Get();
System.RegisterSystem(FInputSystem("Construct From Main"));
System.Update();
```