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
		throw "Error! The length of the bit field must be positive";
	}
	BitLen = len;
	MemLen = (len + 31) / 32;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}
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

	TELEM bitmask = GetMemMask(n);
	int index = GetMemIndex(n);

	pMem[index] = pMem[index] | bitmask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 | n > BitLen) {
		throw "Error! Invalid index";
	}
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 | n > BitLen) {
		throw "Error! Invalid index";
	}
	return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this != &bf) {
		delete[] pMem;
		this->BitLen = bf.BitLen;
		this->MemLen = bf.MemLen;
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
	TBitField res(max(BitLen, bf.BitLen));
	for (int i = 0; i < MemLen; i++) {
		res.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField result = *this;

	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = ~pMem[i];
	
	int bit;
	int pos;
	for (int i = BitLen; i < MemLen * sizeof(TELEM) * 8; i++) {
		bit = i / (sizeof(TELEM) * 8);
		pos = i % (sizeof(TELEM) * 8);

		result.pMem[bit] = result.pMem[bit] & ~GetMemMask(pos);
	}

	return result;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	return ostr;
}