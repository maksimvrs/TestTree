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

QStringList Test::getAnswers() const
{
    return current->answers.keys();
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

void Test::addResult(QString answer)
{
    addQuestion(answer);
}

void Test::clear(TestNode *&from)
{
    if (from != nullptr) {
        for (auto node : from->answers)
            clear(node);
        if (from->result != nullptr)
            delete from->result;
        if (from == current)
            current = from->back;
        delete from;
        from = nullptr;
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

void Test::save(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return;

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();

    bust(head, xml);

    xml.writeEndDocument();
    file.close();
}

void Test::load(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    clear(head);

    QXmlStreamReader xml(&file);
    QString parentAnswer = nullptr;
    while(!xml.atEnd() && !xml.hasError()) {
            QXmlStreamReader::TokenType token = xml.readNext();
            if(token == QXmlStreamReader::StartElement) {
                    if(xml.name() == "QuestionText") {
                        if (head == nullptr) {
                            current = head = new TestNode();
                        }
                        if (current->question.isNull()) {
                            setQuestion(xml.readElementText());
                        }
                        else {
                            addQuestion(parentAnswer);
                            setQuestion(xml.readElementText());
                        }
                    }
                    else if(xml.name() == "AnswerText") {
                        parentAnswer = xml.readElementText();
                        addAnswer(parentAnswer);
                    }
            }
            else if(token == QXmlStreamReader::EndElement) {
                if(xml.name() == "Question") {
                    back();
                }
            }
    }

    file.close();
}

void Test::bust(TestNode *node, QXmlStreamWriter &xml)
{
    if (node == nullptr || node->answers.isEmpty())
        return;
    xml.writeStartElement("Question");
    xml.writeTextElement("QuestionText", node->question);
    for (auto answer: node->answers.keys()) {
        xml.writeStartElement("Answer");
        xml.writeTextElement("AnswerText", answer);
        bust(node->answers.value(answer), xml);
        xml.writeEndElement();
    }
    xml.writeEndElement();
}
