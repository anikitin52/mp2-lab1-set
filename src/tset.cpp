// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{
    if (mp < 0) {
        throw "Error";
    }
}
// Конструктор копирования
TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField)
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}
// Конструктор преобразования типа
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf)
{

}
// Преобразование типа к битовому полю
TSet::operator TBitField()
{
    return BitField;
}
// Доступ к битам
int TSet::GetMaxPower(void) const
{
    return MaxPower;
}
int TSet::IsMember(const int Elem) const
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw "Error!";
    }
    return BitField.GetBit(Elem);
}
void TSet::InsElem(const int Elem)
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw "Error!";
    }
    BitField.SetBit(Elem);
}
void TSet::DelElem(const int Elem)
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw "Error!";
    }
    BitField.ClrBit(Elem);
}
// Теоретико-множественные операции
int TSet::operator==(const TSet& s) const
{
    if (MaxPower != s.MaxPower) {
        return 0;
    }
    return BitField == s.BitField;
}
int TSet::operator!=(const TSet& s) const
{
    return !(*this == s);
}
TSet& TSet::operator=(const TSet& s)
{
    if (this != &s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return *this;
}
TSet TSet::operator+(const int Elem)
{
    TSet res(*this);
    res.InsElem(Elem);
    return res;
}
TSet TSet::operator-(const int Elem)
{
    TSet res(*this);
    res.DelElem(Elem);
    return res;
}
TSet TSet::operator+(const TSet& s)
{
    if (MaxPower != s.MaxPower) {
        throw "Error!";
    }
    return TSet(BitField | s.BitField);
}
TSet TSet::operator*(const TSet& s)
{
    if (MaxPower != s.MaxPower) {
        throw "Error!";
    }
    return TSet(BitField & s.BitField);
}
TSet TSet::operator~()
{
    return TSet(~BitField);
}
// Перегрузка ввода/вывода
istream& operator>>(istream& istr, TSet& s)
{
    int n;
    istr >> n;
    if (n < 0 || n >= s.MaxPower) {
        throw "Error!";
    }
    s.InsElem(n);
    return istr;
}
ostream& operator<<(ostream& ostr, const TSet& s)
{
    ostr << "{";
    bool first = true;
    for (int i = 0; i < s.MaxPower; ++i) {
        if (s.IsMember(i)) {
            if (!first) {
                ostr << ", ";
            }
            ostr << i;
            first = false;
        }
    }
    ostr << "}";
    return ostr;
}