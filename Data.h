#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <sstream>

/**
 * @brief Struct que representa uma data
 */
struct Date {

    int dia; // Dia da data
    int mes; // Mês da data
    int ano; // Ano da data

    // Construtor padrão
    Date() {}

    /**
     * @brief Construtor do struct Date
     * 
     * @param dia Representa o dia da data
     * @param mes Representa o mês da data
     * @param ano Representa o ano da data
     */
    Date(int dia, int mes, int ano)
    {
        this->dia = dia;
        this->mes = mes;
        this->ano = ano;
    }

    /**
     * @brief Retorna o dia do objeto Date
     * @return int 
     */
    int getDia() { return this->dia; }

    /**
     * @brief Altera o dia do objeto Date
     * @param dia Novo dia do objeto Date
     */
    void setDia(int dia) { this->dia = dia; }

    /**
     * @brief Retorna o mês do objeto Date
     * @return int 
     */
    int getMes() { return this->mes; }

    /**
     * @brief Altera o mês do objeto Date
     * @param mes Novo mês do objeto Date
     */
    void setMes(int mes) { this->mes = mes; }

    /**
     * @brief Retorna o ano do objeto Date
     * @return int 
     */
    int getAno() { return this->ano; }

    /**
     * @brief Altera o ano do objeto Date
     * @param ano Novo ano do objeto Date
     */
    void setAno(int ano) { this->ano = ano; }

    /**
     * @brief Sobrecarga do operador 'menor' (<) para o struct Date
     * A função começa comparando com o ano, caso o ano seja igual,
     * compara o mês, caso o mês seja igual, compara o dia.
     * @param data Data a ser comparada
     * @return true 
     * @return false 
     */
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

    /**
     * @brief Sobrecarga do operador 'maior' (>) para o struct Date
     * A função começa comparando com o ano, caso o ano seja igual,
     * compara o mês, caso o mês seja igual, compara o dia.
     * @param data Data a ser comparada
     * @return true 
     * @return false 
     */
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

    /**
     * @brief Sobrecarga do operador 'igual' (==) para o struct Date
     * Para qeu seja retornado true, o ano, mês e dia devem ser iguais
     * @param data Data a ser comparada
     * @return true 
     * @return false 
     */
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

    /**
     * @brief Sobrecarga do operador 'diferente' (!=) para o struct Date
     * @param data Data a ser comparada
     * @return true 
     * @return false 
     */
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

    /**
     * @brief Sobrecarga do operador 'maior ou igual' (>=) para o struct Date
     * @param data  Data a ser comparada
     * @return true 
     * @return false 
     */
    bool operator>=(Date&data) {
        return (*this > data || *this == data);
    }

    /**
     * @brief Sobrecarga do operador 'menor ou igual' (<=) para o struct Date
     * @param data Data a ser comparada
     * @return true 
     * @return false 
     */
    bool operator<=(Date&data) {
        return (*this < data || *this == data);
    }

    /**
     * @brief Sobrecarga do operador de ostream (<<) para o struct Date
     * @param os Objeto de ostream
     * @param data Data a ser impressa
     * @return std::ostream& 
     */
    friend std::ostream &operator<<(std::ostream &os, Date &data)
    {
        os << data.mes << "/" << data.dia << "/" << data.ano;
        return os;
    }

};
#endif // DATE_H