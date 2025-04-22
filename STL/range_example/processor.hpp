//processor.hpp
#pragma once
#include <string>
#include <vector>

// using namespace std;
// 헤더에서는 이거 앵간하면 쓰지마라, 오류 가끔 생기더라

class Processor{
public:
    Processor(std::vector<std::string>data);
    auto transform() -> std::vector<std::string>;
    // template<typename T>
    // auto compute(T value) const -> T; --> 안되서 cpp에서 뺏어옴
    template<typename T>
    auto compute(T value) const -> T{
        if constexpr(std::is_integral_v<T>){
            return value * 2;
        }else if constexpr(std::is_floating_point_v<T>){
            return value / 2;
        }else{
            return value;
        }
    }



private:
    std::vector<std::string> data_;



};