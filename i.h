#ifndef I_H
#define I_H

#include <QObject>

class i : public QObject
{
    Q_OBJECT
public:
    explicit i(QObject *parent = nullptr);

signals:

};

#endif // I_H
