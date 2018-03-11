#include "test.hpp"

Test::Test(QObject *parent) : QObject(parent)
{
    current = head = new TestNode();
}

Test::Test(QString question)
{
    current = head = new TestNode(nullptr, question);
}

Test::~Test()
{
    clear(head);
}

void Test::setQuestion(QString question)
{
    if (current != nullptr) {
        current->question = question;
        emit questionChanged();
    }
}

QString Test::getQuestion() const
{
    return current->question;
}

void Test::addAnswer(QString answer)
{
    if (current != nullptr) {
        if (current->answers.contains(answer))
            emit questionReplaced();
        current->answers[answer] = new TestNode(current);
        emit answerChanged();
    }
}

QStringList Test::getAnswers() const
{
    return current->answers.keys();
}

void Test::addQuestion(QString answer)
{

    if (current != nullptr) {
        if (!current->answers.contains(answer)) {
            addAnswer(answer);
        }
        else {
            // Answer don`t changed
        }
        current = current->answers[answer];
        emit questionChanged();
        emit answerChanged();
    }
}

void Test::addResult(QString answer)
{
    addQuestion(answer);
}

void Test::clear(TestNode *from)
{
    if (from != nullptr && !from->answers.empty()) {
        for (auto node : from->answers)
            clear(node);
        if (from->result != nullptr)
            delete from->result;
        delete from;
    }
    emit questionChanged();
    emit answerChanged();
}

void Test::next(QString answer)
{
    if (current != nullptr && current->answers.contains(answer))
        current = current->answers[answer];
}

void Test::back()
{
    if (current != nullptr && current->back != nullptr) {
        current = current->back;
        emit questionChanged();
        emit answerChanged();
    }
}
