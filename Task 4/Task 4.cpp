#include <fstream>

class Data {
public:
    virtual ~Data() = default;
    virtual std::string print() const = 0;

};

class Data_HTML : public Data {
public:
    Data_HTML(std::string data) : data_(data) {}

    std::string print() const override {
        return "<html>" + data_ + "<html/>";
    }

private:
    std::string data_;
};

class Data_JSON : public Data {
public:
    Data_JSON(std::string data) : data_(data) {}

    std::string print() const override {
        return "{ \"data\": \"" + data_ + "\"}";
    }

private:
    std::string data_;
};

class Data_TEXT : public Data {
public:
    Data_TEXT(std::string data) : data_(data) {}

    std::string print() const override {
        return data_;
    }

private:
    std::string data_;
};


void Save(std::ofstream& file, const Data& d) {
    file << d.print() << std::endl;
}