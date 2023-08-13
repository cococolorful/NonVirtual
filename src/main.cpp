#include <iostream>

#include <virtual.h>
#include <non_virtual.h>

int main()
{
    {
        auto& System = Virtual::FSystemManager::Get();
        System.Update();
    }
    std::cout << "---------------------------------\n";
    {
        auto& System =
            NonVirtual::FSystemManagerVariant<NonVirtual::FAudioSystem,
                                              NonVirtual::FInputSystem>::Get();
        System.Update();
    }
    std::cout << "---------------------------------\n";
    {
        auto& System = NonVirtual::FSystemManagerTupleVector<
            NonVirtual::FInputSystem, NonVirtual::FAudioSystem>::Get();
        System.RegisterSystem(NonVirtual::FInputSystem("Construct From Main"));
        System.Update();
    }
}