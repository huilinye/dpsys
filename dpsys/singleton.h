#pragma once
#include <memory>
namespace dpsys {
template<typename T>
class SingletonPtr {
public:
    static std::shared_ptr<T> getInstance() {

        static std::shared_ptr<T> instance = std::make_shared<T>();
        return instance;

    }

};

} // namespace dpsys

    

