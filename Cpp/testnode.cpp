#include "testnode.hpp"

TestNode::TestNode()
{
    this->back = nullptr;
    this->result = nullptr;
}

TestNode::TestNode(TestNode *back)
{
    this->back = back;
    this->result = nullptr;
}

TestNode::TestNode(TestNode *back, QString question)
{
    this->back = back;
    this->question = question;
}

TestNode::~TestNode()
{
    delete result;
}
