#ifndef TEST_HPP
#define TEST_HPP

#include <QObject>

#include "testnode.hpp"

class Test : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString question READ getQuestion WRITE setQuestion NOTIFY questionChanged)
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
    void setResult(Result*);

    Q_INVOKABLE void next(QString);
    Q_INVOKABLE void back();

    Q_INVOKABLE void clear(TestNode*);

signals:
    void questionReplaced();
    void questionChanged();
    void answerChanged();

public slots:

private:
    TestNode *head;
    TestNode *current;
};

#endif // TEST_HPP
