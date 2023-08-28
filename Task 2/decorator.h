#pragma once
#include <iostream>

class Text {
public:
    virtual void render(const std::string& data) const;
};

class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text);
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text);
    void render(const std::string& data)  const;
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text);
    void render(const std::string& data) const;
};

class ParagraphText : public DecoratedText {
public:
    explicit ParagraphText(Text* text);
    void render(const std::string& data) const;
};

class ReversedText : public DecoratedText {
public:
    explicit ReversedText(Text* text);    
    void render(std::string data) const;
};

class LinkText : public DecoratedText {
public:
    explicit LinkText(Text* text);
    void render(const std::string& link, const std::string& data) const;
};

void StartTextDecorator();