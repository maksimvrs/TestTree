#ifndef RESULT_HPP
#define RESULT_HPP

#include <QObject>

class Result : public QObject
{
    Q_OBJECT
public:
    explicit Result(QObject *parent = nullptr);

signals:

public slots:
};

#endif // RESULT_HPP
