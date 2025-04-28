// ex17_final2.cpp
#include <iostream>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

enum class ColumnType{
    INT,
    STRING,
    FLOAT,
    BOOL
};

struct Column{
    std::string name;
    std::string value;
};

struct Row{
    std::vector<Column> columns;

    void addColumn(const std::string &name, const std::string &value){
        columns.push_back(Column{name, value});
    }

    void print() const{
        for (const auto &col : columns){
            std::cout << col.name << "=" << col.value << " ";
        }
        std::cout << "\n";
    }
};

class ThreadSafeDB{
private:
    std::unordered_map<int, std::shared_ptr<Row>> db;
    std::unordered_map<std::string, ColumnType> schema;
    mutable std::shared_mutex mutex;

public:
    void registerColumn(const std::string &name, ColumnType type){
        std::unique_lock lock(mutex);
        schema[name] = type;
        std::cout << "컬럼 등록됨: " << name << " (";
        switch (type){
            case ColumnType::INT:
                std::cout << "INT";
                break;
            case ColumnType::STRING:
                std::cout << "STRING";
                break;
            case ColumnType::FLOAT:
                std::cout << "FLOAT";
                break;
            case ColumnType::BOOL:
                std::cout << "BOOL";
                break;
        }
        std::cout << ")\n";
    }

    void insert(int key, const std::vector<Column> &columns){
        std::unique_lock lock(mutex);
        auto row = std::make_shared<Row>();
        for (const auto &col : columns){
            if (schema.find(col.name) == schema.end()){
                throw std::runtime_error("정의되지 않은 컬럼: " + col.name);
            }
            // 🔍 타입 검사 생략 가능, 문자열 기반
            row->addColumn(col.name, col.value);
        }
        db[key] = row;
    }

    void printAll() const {
        std::shared_lock lock(mutex);
        for (const auto &[key, row] : db){
            std::cout << key << ": ";
            row->print();
        }
    }
};

int main(){
    ThreadSafeDB db;

    db.registerColumn("id", ColumnType::INT);
    db.registerColumn("name", ColumnType::STRING);
    db.registerColumn("active", ColumnType::BOOL);

    db.insert(1, {{"id", "101"}, {"name", "Alice"}, {"active", "true"}});
    db.insert(2, {{"id", "102"}, {"name", "Bob"}, {"active", "false"}});

    db.printAll();

    return 0;
}