//processor.cpp
#include "processor.hpp"
#include <algorithm>

Processor::Processor(std::vector<std::string>data) : data_(data){

}
auto Processor::transform() -> std::vector<std::string>{
    auto result = data_;
    for (auto& s : result){
        if (s.empty()){
            s = "empty";
        }else{
            s = s + "_processed"; // string class + "..."라서 가능 리터럴상수끼리는 더하기로 못함
        }
        
    }
    return result;
}

// template<typename T>
// auto Processor::compute(T value) const -> T{
//     if constexpr(std::is_integral_v<T>){
//         return value * 2;
//     }else if constexpr(std::is_floating_point_v<T>){
//         return value / 2;
//     }else{
//         return value;
//     }
// }--->이거 안되서 헤더로 넘김
