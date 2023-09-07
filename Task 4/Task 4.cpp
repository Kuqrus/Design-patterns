#include <fstream>

class Data {
public:
    enum class Type {
        Text,
        HTML,
        JSON
    };

    virtual ~Data() = default;
    virtual std::string print() const = 0;
    virtual Type type() const = 0;
};

class Data_HTML : public Data {
public:
    Data_HTML(std::string data) : data_(data) {}

    Type type() const override { return Type::HTML; }

    std::string print() const override {
        return "<html>" + data_ + "<html/>";
    }

private:
    std::string data_;
};

class Data_JSON : public Data {
public:
    Data_JSON(std::string data) : data_(data) {}

    Type type() const override { return Type::JSON; }

    std::string print() const override {
        return "{ \"data\": \"" + data_ + "\"}";
    }

private:
    std::string data_;
};

class Data_TEXT : public Data {
public:
    Data_TEXT(std::string data) : data_(data) {}

    Type type() const override { return Type::Text; }

    std::string print() const override {
        return data_;
    }

private:
    std::string data_;
};


void Save(std::ofstream& file, const Data& d) {
    file << d.print() << std::endl;
}

void SaveAsHTML(std::ofstream& file, const Data& d) {
    if (d.type() != Data::Type::HTML) {
        throw std::runtime_error("Wrong format! Use HTML data type");
    }
    file << d.print() << std::endl;
}

void SaveAsJSON(std::ofstream& file, const Data& d) {
    if (d.type() != Data::Type::JSON) {
        throw std::runtime_error("Wrong format! Use JSON data type");
    }
    file << d.print() << std::endl;
}

void SaveAsText(std::ofstream& file, const Data& d) {
    if (d.type() != Data::Type::Text) {
        throw std::runtime_error("Wrong format! Use Text data type");
    }
    file << d.print() << std::endl;
}