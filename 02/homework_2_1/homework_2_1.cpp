//Домашнее задание к занятию «Структурные шаблоны». Задание 1.

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};

class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(std::string data) const {
        std::reverse(data.begin(), data.end());
        text_->render(data);
    }
};

class Paragraph : public DecoratedText{
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render(std::string link, const std::string& data) {
        std::cout << "<a href=" << link << ">";
        text_->render(data);
        std::cout << "</a>";
    }
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

int main() {
    auto text_block1 = new Paragraph(new Text());
    text_block1->render("Hello world");
    std::cout << std::endl;

    auto text_block2 = new Reversed(new Text());
    text_block2->render("Hello world");
    std::cout << std::endl;

    auto text_block3 = new Link(new Text());
    text_block3->render("netology.ru", "Hello world");
    std::cout << std::endl;

    return 0;
}