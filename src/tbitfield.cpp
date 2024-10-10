// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{	
	if (len <= 0) {
		throw "Error!";
	}

	BitLen = len;
	MemLen = (BitLen + sizeof(TELEM) * 8) / (sizeof(TELEM) * 8);
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}
//+ + + + + +
TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return TELEM(1) << (sizeof(TELEM) * 8 - n - 1);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen)) {
		throw "Error!";
	}
	int ind = n / (sizeof(TELEM) * 8);
	int pos = n % (sizeof(TELEM) * 8);
	pMem[ind] = pMem[ind] | GetMemMask(pos);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen)) throw "Wrong index";

	int NVar = n / (sizeof(TELEM) * 8);
	int NBit = n % (sizeof(TELEM) * 8);

	pMem[NVar] = pMem[NVar] & ~GetMemMask(NBit);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 | n > BitLen) {
		throw "Error!";
	}
	return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this != &bf) {
		this->BitLen = bf.BitLen;
		this->MemLen = bf.MemLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			this->pMem[i] = bf.pMem[i];
		}
	}
	return *this;
	
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{	
	if (BitLen != bf.BitLen) {
		return 0;
	}
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i]) {
			return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen) {
		return 1;
	}
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i]) {
			return 1;
		}
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	TBitField res(max(BitLen, bf.BitLen));
	for (int i = 0; i < MemLen; i++) {
		res.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	TBitField res = TBitField(max(BitLen, bf.BitLen)); 
	for (int i = 0; i < min(MemLen, bf.MemLen); i++) {
		res.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField result = *this; //123456789
	int pos;
	int bit_pos;
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = ~pMem[i];

	for (int i = BitLen; i < MemLen * sizeof(TELEM) * 8; i++) {
		pos = i / (sizeof(TELEM) * 8);
		bit_pos = i % (sizeof(TELEM) * 8);

		result.pMem[pos] = result.pMem[pos] & ~GetMemMask(bit_pos);
	}
	return result;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	char bit;
	for (int i = 0; i < bf.BitLen; i++) {
		istr >> bit;
		if (bit == '0') {
			bf.ClrBit(i);
		}
		else if (bit == '1') {
			bf.SetBit(i);
		}
		else {
			throw "Error";
		}
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++) {
		ostr << bf.GetBit(i);
	}
	return ostr;
}