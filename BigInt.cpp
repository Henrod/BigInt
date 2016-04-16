#include<iostream>
#include<cmath>
#include<stdexcept>

using namespace std;

class BigInt {
	private:
		int* mNum;
		int mSize;
		void setNum(int value);
		void setNum(const BigInt& value);
		void shiftLeft(int shift);
		void shiftRight(int shift);
	public:
		BigInt(int size = 1);
		~BigInt();
		BigInt operator+ (BigInt& x);
		BigInt operator* (int value) const;
		static BigInt fact (int value);
		BigInt(const BigInt& value);
		BigInt& operator= (int value);
		BigInt& operator= (const BigInt& value);
		int operator[] (int index) const;
		void print() const;
		int getSize() const { return mSize; };
		void set(int index, int value);
};

BigInt::BigInt(int size) {
	mNum = new int[size];
       	mSize = size;

	for (int i = 0; i < size; ++i)
		mNum[i] = 0; 
}

void BigInt::set(int index, int value) {
	mNum[index] = value;
}

BigInt::~BigInt() {
	delete[] mNum;
}

void BigInt::print() const {
	for (int i = 0; i < mSize; ++i) {
		cout << mNum[i];
	}

	cout << endl;
}

int BigInt::operator[] (int index) const {
	if (index < 0 || index >= mSize) throw -1;
	return mNum[index];
}

BigInt BigInt::operator+(BigInt& x) {
	int size = x.getSize();
	if (size < mSize) {
		x.shiftRight(mSize - size);
		size = mSize;
	} else {
		this->shiftRight(size - mSize);
	}

	BigInt res = BigInt(size);

	int carryOut = 0;

	for (int i = size - 1; i >= 0; --i) {
		int sum = x[i] + mNum[i] + carryOut;
		res.set(i, sum % 10);
		carryOut = sum / 10;

		if (i == 0 && carryOut != 0) {
			res.shiftRight(1);
			res.set(0, carryOut);
		}
	}

	return res;
}

void BigInt::shiftRight(int shift) {
	if (shift == 0) return;

	int* newInt = new int[mSize + shift];
	for (int i = 0; i < shift; ++i) 
		newInt[i] = 0;

	for (int i = 0; i < mSize; ++i) 
		newInt[i + shift] = mNum[i];

	mSize += shift;
	delete[] mNum;
	mNum = newInt;
}

BigInt BigInt::operator* (int value) const {
	BigInt op;
	op = value;

	int size = op.getSize();
	if (size < mSize) size = mSize;

	BigInt res = BigInt(size);

	for (int i = op.getSize() - 1, shift = 0; i >= 0; --i) {
		int carryOut = 0;
		BigInt tmp = BigInt(size);
		for (int j = mSize - 1; j >= 0; --j) {
			int mult = op[i] * mNum[j] + carryOut;
			tmp.set(j, mult % 10);
			carryOut = mult / 10;

			if (j == 0 && carryOut != 0) {
				tmp.shiftRight(1);
				tmp.set(0, carryOut);
			}
		}

		tmp.shiftLeft(shift++);
		res = res + tmp;
	}


	return res;
}

void BigInt::shiftLeft(int shift) {
	if (shift == 0) return;

	int* newInt = new int[shift + mSize];

	for (int i = 0; i < mSize; ++i)
		newInt[i] = mNum[i];
	for (int i = mSize; i < shift + mSize; ++i)
		newInt[i] = 0;
	mSize += shift;

	delete[] mNum;
	mNum = newInt;
}

BigInt::BigInt(const BigInt& value) {
	setNum(value);
}

BigInt& BigInt::operator=(int value) {
	setNum(value);
	return *this;
}

BigInt& BigInt::operator=(const BigInt& value) {
	setNum(value);
	return *this;
}

void BigInt::setNum(const BigInt& value) {
	int size = value.getSize();

	delete[] mNum;
	mNum = new int[size];
	mSize = size;

	for (int i = 0; i < size; ++i) {
		mNum[i] = value[i];
	}
}

void BigInt::setNum(int value) {
	int div = 10;
	int size = 1;
	while (value / div != 0) {
		div *= 10;
		++size;
	}

	delete[] mNum; 
	mNum = new int[size];
	mSize = size;

	for (int i = 0; i < size; ++i) {
		div /= 10;
		int alg = value / div;
		value = value % div;
		
		mNum[i] = alg;
	}
}

BigInt BigInt::fact (int value) {
	BigInt res;
	res = 1;

	for (int i = 2; i <= value; ++i) {
		res = res * i;
	}

	return res;
}

int main() {
	BigInt a;
	a = 1;
	a = BigInt::fact(100);
	a.print();
	
	/*for (int i = 0; i < 81; ++i) {
		a = BigInt::fact(i);
		a.print();
	}*/

	return 0;
}
