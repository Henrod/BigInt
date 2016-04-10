#include<iostream>
#include<cmath>

using namespace std;

class BigInt {
	private:
		int* mNum;
		int mSize;
		void copy(int size);
		void setNum(int value);
		void setNum(const BigInt& value);
	public:
		BigInt(int size = 1) : mSize(size), mNum(new int[mSize]){ mNum[0] = 0; };
		~BigInt();
		BigInt operator+ (const BigInt& x);
		BigInt& operator= (int value);
		BigInt& operator= (const BigInt& value);
		int operator[] (int index) const;
		void print() const;
		int getSize() const { return mSize; };
		void set(int index, int value);
};

void BigInt::set(int index, int value) {
	mNum[index] = value;
}

BigInt::~BigInt() {
	delete mNum;
}

void BigInt::print() const {
	for (int i = 0; i < mSize; ++i) {
		cout << mNum[i];
	}

	cout << endl;
}

int BigInt::operator[] (int index) const {
	return mNum[index];
}

BigInt BigInt::operator+(const BigInt& x) {
	int size = x.getSize();

	if (mSize < size) {
		copy(size);
	} else {
		size = mSize;
	}

	BigInt res = BigInt(size);

	int carryOut = 0;

	for (int i = size - 1; i >= 0; --i) {
		int sum = x[i] + mNum[i] + carryOut;
		res.set(i, sum % 10);
		carryOut = sum / 10;

		if (i == 0 && carryOut != 0) {
			res.copy(size+1);
			res.set(0, carryOut);
		}
	}


	return res;
}

void BigInt::copy(int size) {
	int* bigInt = new int[size];
	int start = size - mSize;

	for (int i = 0; i < mSize; ++i) {
		bigInt[i + start] = mNum[i];
	}

	delete mNum;
	mNum = bigInt;
	mSize = size;

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

	delete mNum;
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

	delete mNum;
	mNum = new int[size];
	mSize = size;

	for (int i = 0; i < size; ++i) {
		div /= 10;
		int alg = value / div;
		value = value % div;
		
		mNum[i] = alg;
	}
}

int main() {
	BigInt a;
	a = 999999999;
	BigInt b;
	b = 999999999;
	BigInt c;

	a.print();
	b.print();
	c = a + b;
	c.print();

}
