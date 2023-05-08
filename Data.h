#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <sstream>

class Date {

    private:
        int dia, mes, ano;
    public:
        Date();
        Date(int mes, int dia, int ano) {
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

        void print() { std::cout << this->getMes() << "/" << this->getDia() << "/" << this->getAno() << std::endl; }

        std::string strPrint() {
            std::stringstream ss;
            ss << getMes() << "/" << getDia() << "/" << getAno();
            return ss.str();
        }

        bool operator<(Date& data) {
            if (this->getAno() < data.getAno()) {
                return true;
            } else if (this->getAno() == data.getAno()) {
                if (this->getMes() < data.getMes()) {
                    return true;
                } else if (this->getMes() == data.getMes()) {
                    if (this->getDia() < data.getDia()) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }

        bool operator>(Date& data) {
            if (this->getAno() > data.getAno()) {
                return true;
            } else if (this->getAno() == data.getAno()) {
                if (this->getMes() > data.getMes()) {
                    return true;
                } else if (this->getMes() == data.getMes()) {
                    if (this->getDia() > data.getDia()) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }

        bool operator==(Date& data) {
            if (this->getAno() == data.getAno() && this->getMes() == data.getMes() && this->getDia() == data.getDia()) {
                return true;
            } else {
                return false;
            }
        }

        bool operator!=(Date& data) {
            if (this->getAno() != data.getAno() || this->getMes() != data.getMes() || this->getDia() != data.getDia()) {
                return true;
            } else {
                return false;
            }
        }

        friend std::ostream& operator<<(std::ostream& os, Date& data) {
            os << data.mes << "/" << data.dia << "/" << data.ano;
            return os;
        }


};
#endif // DATE_H