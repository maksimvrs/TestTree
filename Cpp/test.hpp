#ifndef TEST_HPP
#define TEST_HPP

#include <QObject>
#include <QFile>
#include <QStandardPaths>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include "testnode.hpp"

class Test : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString question READ getQuestion WRITE setQuestion NOTIFY questionChanged)
    Q_PROPERTY(QString result READ getResult WRITE setResult NOTIFY resultChanged)
    Q_PROPERTY(QStringList answers READ getAnswers NOTIFY answerChanged)

public:
    explicit Test(QObject *parent = nullptr);
    explicit Test(QString);
    ~Test();

    Q_INVOKABLE void addQuestion(QString);
    void setQuestion(QString);
    QString getQuestion() const;

    Q_INVOKABLE void addAnswer(QString);
    QStringList getAnswers() const;

    Q_INVOKABLE void addResult(QString);
    void addResult(QString, QString);
    void setResult(QString);
    QString getResult();

    Q_INVOKABLE void next(QString);
    Q_INVOKABLE void back();
    Q_INVOKABLE bool isResult();
    Q_INVOKABLE bool nextIsResult(QString);

    Q_INVOKABLE void clear(TestNode*&);

    Q_INVOKABLE void load(QString);
    Q_INVOKABLE void save(QString);

signals:
    void questionReplaced();
    void questionChanged();
    void answerChanged();
    void resultChanged();
    void resultOpen();

public slots:

private:
    TestNode *head;
    TestNode *current;

    void bust(TestNode*, QXmlStreamWriter&);
};

#endif // TEST_HPP
