#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <includes.h>

class Account
{
    QString name;
    QString phone;
    QDate birthday;
    QString country;
    QString city;
    bool sex;
    int age;
public:
    Account();
    Account(QString name);
    ~Account();
    QString getName() const;
    void setName(const QString &value);
    QString getPhone() const;
    void setPhone(const QString &value);
    QDate getBirthday() const;
    void setBirthday(const QDate &value);
    QString getCountry() const;
    void setCountry(const QString &value);
    QString getCity() const;
    void setCity(const QString &value);
    bool getSex() const;
    void setSex(bool value);
    int getAge() const;
    void setAge(int value);
};

#endif // ACCOUNT_H
