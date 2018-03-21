#include "testnode.hpp"

TestNode::TestNode()
{
    this->back = nullptr;
    isResult = false;
}

TestNode::TestNode(TestNode *back)
{
    this->back = back;
    isResult = false;
}

TestNode::TestNode(TestNode *back, QString question)
{
    this->back = back;
    isResult = false;
    this->question = question;
}

TestNode::~TestNode()
{

}
