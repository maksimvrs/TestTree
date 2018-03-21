#ifndef TESTNODE_HPP
#define TESTNODE_HPP

#include <QString>
#include <QMap>
#include <QQuickTextDocument>

class TestNode
{
public:
    TestNode();
    TestNode(TestNode*);
    TestNode(TestNode*, QString);

    QString question;

    QMap<QString, TestNode*> answers;

    TestNode *back;

    bool isResult;
    QString result;

    ~TestNode();
};

#endif // TESTNODE_HPP
