#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <sstream>

struct Date
{
    int dia;
    int mes;
    int ano;

    Date() {}

    Date(int dia, int mes, int ano)
    {
        this->dia = dia;
        this->mes = mes;
        this->ano = ano;
    }

    int getDia() { return this->dia; }

    void setDia(int dia) { this->dia = dia; }

    int getMes() { return this->mes; }

    void setMes(int mes) { this->mes = mes; }

    int getAno() { return this->ano; }

    void setAno(int ano) { this->ano = ano; }

    bool operator<(Date &data)
    {
        if (this->getAno() < data.getAno())
        {
            return true;
        }

        else if (this->getAno() == data.getAno())
        {

            if (this->getMes() < data.getMes())
            {
                return true;
            }

            else if (this->getMes() == data.getMes())
            {
                if (this->getDia() < data.getDia())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    bool operator>(Date &data)
    {
        if (this->getAno() > data.getAno())
        {
            return true;
        }

        else if (this->getAno() == data.getAno())
        {
            if (this->getMes() > data.getMes())
            {
                return true;
            }

            else if (this->getMes() == data.getMes())
            {
                if (this->getDia() > data.getDia())
                {
                    return true;
                }

                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    bool operator==(Date &data)
    {
        if (this->getAno() == data.getAno() && this->getMes() == data.getMes() && this->getDia() == data.getDia())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!=(Date &data)
    {
        if (this->getAno() != data.getAno() || this->getMes() != data.getMes() || this->getDia() != data.getDia())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator>=(Date&data) {
        return (*this > data || *this == data);
    }

    bool operator<=(Date&data) {
        return (*this < data || *this == data);
    }

    friend std::ostream &operator<<(std::ostream &os, Date &data)
    {
        os << data.mes << "/" << data.dia << "/" << data.ano;
        return os;
    }

    int& operator[](int index) {
        switch (index) {
            case 0:
                return dia;
            case 1:
                return mes;
            case 2:
                return ano;
            default:
                throw std::out_of_range("Index out of range");
        }
    }
};
#endif // DATE_H