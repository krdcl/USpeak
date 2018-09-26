#include "account.h"


QString Account::getName() const
{
    
    return name;
}

void Account::setName(const QString &value)
{
    name = value;
}

QString Account::getPhone() const
{
    return phone;
}

void Account::setPhone(const QString &value)
{
    phone = value;
}

QDate Account::getBirthday() const
{
    return birthday;
}

void Account::setBirthday(const QDate &value)
{
    birthday = value;
}

QString Account::getCountry() const
{
    return country;
}

void Account::setCountry(const QString &value)
{
    country = value;
}

QString Account::getCity() const
{
    return city;
}

void Account::setCity(const QString &value)
{
    city = value;
}

bool Account::getSex() const
{
    return sex;
}

void Account::setSex(bool value)
{
    sex = value;
}

int Account::getAge() const
{
    return age;
}

void Account::setAge(int value)
{
    age = value;
}
Account::Account()
{

}

Account::Account(QString name)
{
    this->name = name;
}

Account::~Account()
{

}

