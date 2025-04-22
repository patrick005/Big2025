//data_process.hpp
#pragma once
#include <string>
#include <vector>

class DataProcessor{
    public:
    DataProcessor(std::vector<std::string> data);
    auto sort_by_length() -> std::vector<std::string>; // 리턴 타입 명시를 하기위한 표기법
    // std::vector<std::string> sort_by_length(); //위에줄과 동일함, 이건 취향차이
    auto filter_by_prefix(const std::string &prefix) -> std::vector<std::string>;
    std::vector<std::string> data_;
};