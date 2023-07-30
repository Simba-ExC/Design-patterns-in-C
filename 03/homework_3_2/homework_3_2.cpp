// Домашнее задание к занятию «Поведенческие шаблоны». Задание 2.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Observer {
public:
    virtual void onWarning(const std::string& message) {};
    virtual void onError(const std::string& message) {};
    virtual void onFatalError(const std::string& message) {};
protected:
    std::string message_;
};

class WarningObserver : public Observer {
public:
    virtual void onWarning(const std::string& message) override {
        this->message_ = message;
        std::cout << "WARNING: " << message << std::endl;
    }
};

class ErrorObserver : public Observer {
public:
    ErrorObserver(std::ofstream& f) : file_(f) {};

    virtual void onError(const std::string& message) override {
        this->message_ = message;
        if (file_.is_open()) {
            file_ << "ERROR: " << message << std::endl;
        }
        else
            std::cout << "File not open" << std::endl;
    }
private:
    std::ofstream& file_;
};

class FatalErrorObserver : public Observer {
public:
    FatalErrorObserver(std::ofstream& f) : file_(f) {};

    virtual void onFatalError(const std::string& message) override {
        this->message_ = message;
        std::cout << "FATAL ERROR: " << message << std::endl;
        if (file_.is_open()) {
            file_ << "FATAL ERROR: " << message << std::endl;
        }
        else
            std::cout << "File not open" << std::endl;
    }
private:
    std::ofstream& file_;
};

class Subject {
public:
    void addObserver(Observer& observer) {
        observers_.push_back(&observer);
    }
    void removeObserver(Observer* subscriber) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), subscriber), observers_.end());
    }
    void warning(const std::string& message) const {
        for (auto& sub : observers_) {
            sub->onWarning(message);
        }
    }
    void error(const std::string& message) const {
        for (auto& sub : observers_) {
            sub->onError(message);
        }
    }
    void fatalError(const std::string& message) const {
        for (auto& sub : observers_) {
            sub->onFatalError(message);
        }
    }
private:
    std::vector<Observer*> observers_;
};

//___________________________________________________________________________

int main(int argc, char** argv) {
    std::ofstream file("file.txt");
    const std::string message = "message";
    Subject subj;

    WarningObserver w;
    ErrorObserver e(file);
    FatalErrorObserver fe(file);

    subj.addObserver(w);
    subj.warning(message);
    subj.addObserver(e);
    subj.error(message);
    subj.addObserver(fe);
    subj.fatalError(message);

    file.close();
    return 0;
}