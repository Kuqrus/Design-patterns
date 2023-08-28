#include "decorator.h"

void Text::render(const std::string& data) const {
    std::cout << data;
}

DecoratedText::DecoratedText(Text* text) : text_(text) {}

ItalicText::ItalicText(Text* text) : DecoratedText(text) {}
void ItalicText::render(const std::string& data)  const {
    std::cout << "<i>";
    text_->render(data);
    std::cout << "</i>";
}

BoldText::BoldText(Text* text) : DecoratedText(text) {}
void BoldText::render(const std::string& data) const {
    std::cout << "<b>";
    text_->render(data);
    std::cout << "</b>";
}

ParagraphText::ParagraphText(Text* text) : DecoratedText(text) {}
void ParagraphText::render(const std::string& data) const {
    std::cout << "<p>";
    text_->render(data);
    std::cout << "</p>";
}

ReversedText::ReversedText(Text* text) : DecoratedText(text) {}
void ReversedText::render(std::string data) const {
    std::reverse(data.begin(), data.end());
    text_->render(data);
}

LinkText::LinkText(Text* text) : DecoratedText(text) {}
void LinkText::render(const std::string& link, const std::string& data) const {
    std::cout << "<a href=" << link << ">";
    text_->render(data);
    std::cout << "</a>";
}

void StartTextDecorator() {
    auto paragraph = new ParagraphText(new BoldText(new Text()));
    paragraph->render("Hello world");

    std::cout << std::endl;

    auto reversed = new ReversedText(new ItalicText(new Text()));
    reversed->render("Hello Netology");

    std::cout << std::endl;

    auto linkMore = new LinkText(new BoldText(new Text()));
    linkMore->render("vk.com", "Vkontakte");

    std::cout << std::endl;
}