#ifndef TESTNODE_HPP
#define TESTNODE_HPP

#include <QString>
#include <QMap>

#include "result.hpp"

class TestNode
{
public:
    TestNode();
    TestNode(TestNode*);
    TestNode(TestNode*, QString);

    QString question;

    QMap<QString, TestNode*> answers;

    TestNode *back;

    Result *result;

    ~TestNode();
};

#endif // TESTNODE_HPP
