#include "test.hpp"

#include <QDir>

Test::Test(QObject *parent) : QObject(parent)
{
    current = head = new TestNode();
//    load("test_1.xml");
}

Test::Test(QString question)
{
    current = head = new TestNode(nullptr, question);
//    load("test_1.xml");
}

Test::~Test()
{
//    save("test_1.xml");
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
    if (current != nullptr)
        return current->question;
    return nullptr;
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
    if (current != nullptr)
        return current->answers.keys();
    return QStringList();
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
    addResult(answer, "");
}

void Test::addResult(QString answer, QString result = "")
{
    addAnswer(answer);
    if (current != nullptr &&
        current->answers.contains(answer))
            current->answers[answer]->result = result;
}

void Test::setResult(QString result)
{
    if (current != nullptr)
        current->result = result;
}

bool Test::isResult(QString answer = nullptr)
{
    if (current == nullptr)
        return false;
    if (answer.isNull())
        return !current->result.isNull();
    if (current->answers.contains(answer))
        return !current->answers[answer]->result.isNull();
    return false;
}

void Test::clear(TestNode *&from)
{
    if (from != nullptr) {
        for (auto node : from->answers)
            clear(node);
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
    if (!current->result.isNull())
        emit result();
    else {
        emit questionChanged();
        emit answerChanged();
    }
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
    QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QFile file(path + "/" + fileName);
    qDebug() << file.fileName();
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << file.errorString();
        return;
    }

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();

    bust(head, xml);

    xml.writeEndDocument();
    file.close();
}

void Test::load(QString fileName)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QFile file(path + "/" + fileName);
    qDebug() << file.fileName();
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return;
    }

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
                    else if(xml.name() == "ResultText") {
                        QString result = xml.readElementText();
                        qDebug() << result.isNull();
                        addResult(parentAnswer, result);
                    }
            }
            else if(token == QXmlStreamReader::EndElement) {
                if(xml.name() == "Question") {
                    back();
                }
            }
    }

    qDebug() << xml.text();

    file.close();
}

void Test::bust(TestNode *node, QXmlStreamWriter &xml)
{
    if (node == nullptr)
        return;
    if (!node->result.isNull()) {
        xml.writeStartElement("Result");
        xml.writeTextElement("ResultText", node->result);
        xml.writeEndElement();
        return;
    }
    else {
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
}
