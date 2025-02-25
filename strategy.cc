// Privet
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include <numeric>
#include <iterator>
#include <sstream>
#include <cctype>
class DataSource{
public:
    virtual ~DataSource() = default;
    virtual std::vector<std::string> getLines() = 0;
};


class FileSource : public DataSource{
    std::string _file;
public:
    FileSource(const std::string& file) : _file(file) {}
    std::vector<std::string> getLines() override{
        std::vector<std::string> lines;
        std::ifstream file(_file);
        for (std::string line; std::getline(file, line); ) {
            lines.push_back(line);
        }
        return lines;
    }    
};


class BalanceProcessor{
public:
void  process(DataSource& book){
    std::unordered_map<std::string, int> total_balance;
    auto lines = book.getLines();
    for (const auto& line : lines){
        std::size_t pos = line.find(":");
        std::string sales;

        std::string name = line.substr(0, pos + 1);
        sales = line.substr(pos + 1, line.size() - 1);
        std::istringstream iss(sales);
        std::vector<int> vec{std::istream_iterator<int>(iss), 
                             std::istream_iterator<int>()};
        name.pop_back();
        total_balance[name] += std::accumulate(std::begin(vec), std::end(vec), 0);
    }

    for (const auto& [key, val] : total_balance){
        std::cout << key << ":\t" << val << std::endl;
    }
}


};

int main(){
    FileSource filesource("input");
    BalanceProcessor processor;
    processor.process(filesource);

    return EXIT_SUCCESS;
}
