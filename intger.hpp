#pragma once
#ifndef BigIntger
#define BigIntger

#include<vector>
#include<string>
#include<iostream>
#include<iomanip>
#include<algorithm>
using std::vector;
using std::string;
using std::istream;
using std::ostream;

int max(int a, int b)
{
	if (a > b) return a;
	else return b;
}

class Int
{
	vector<int> data;
	static const int oo = 10000;
	bool bo;

	const int operator [](int x) const
	{
		return data[x];
	}

	int &operator [](int x)
	{
		return data[x];
	}

	void push_back(int x)
	{
		data.push_back(x);
	}

	void pop_back() 
	{
		data.pop_back(); 
	}

	const int size() const
	{
		return data.size();
	}

	void clear() 
	{ 
		data.clear(), bo = 0; 
	}

	bool cmp(const Int &b, int t)
	{
		for (int i = b.size() - 1; i >= 0; i--)
		{
			if (data[i + t] > b[i]) return 1;
			if (data[i + t] < b[i]) return 0;
		}
		return 1;
	}

	void dec(const Int &a, int t)
	{
		for (int i = 0; i < a.size(); i++)
		{
			data[i + t] -= a[i];
			if (data[i + t] < 0) data[i + t + 1]--, data[i + t] += oo;
		}
	}

public:
	Int()
	{
		data.clear(); data.push_back(0);
		bo = 0;
	}

	Int(int x)
	{
		data.clear(); bo = 0;
		if (x < 0) x = -x, bo = 1;
		for (; x; x /= oo) data.push_back(x%oo);
	}

	friend Int abs(const Int &a)
	{
		if (a.neg()) return -a;
		else return a;
	}

	const int length() const
	{
		int ans = (size() - 1) * 4;
		for (int x = data[size() - 1]; x; x /= 10) ans++;
		return ans;
	}

	const bool neg() const
	{
		return bo;
	}

	Int operator -() const
	{
		Int ans = *this;
		ans.bo ^= 1;
		return ans;
	}

	Int operator = (const Int &x)
	{
		data = x.data, bo = x.bo;
		return *this;
	}

	friend bool operator ==(const Int &a, const Int &b)
	{
		if (a.bo != b.bo) return 0;
		if (a.size() != b.size()) return 0;
		for (int i = 0; i < a.size(); i++)
			if (a[i] != b[i]) return 0;
		return 1;
	}

	friend bool operator > (const Int &a, const Int &b)
	{
		return !(a < b) && a != b;
	}

	friend bool operator >= (const Int &a, const Int &b)
	{
		return !(a < b);
	}

	friend bool operator <= (const Int &a, const Int &b)
	{
		return a < b || a == b;
	}

	friend bool operator < (const Int &a, const Int &b)
	{
		if (a.bo != b.bo) return a.bo > b.bo;
		if (!a.bo)
		{
			if (a.size() != b.size()) return a.size() < b.size();
			for (int i = a.size() - 1; i >= 0; i--)
			{
				if (a[i] != b[i]) return a[i] < b[i];
			}
			return 0;
		}
		else return -a > -b;
	}

	friend bool operator != (const Int &a, const Int &b)
	{
		return !(a == b);
	}

	Int operator += (const Int &a)
	{
		return *this = *this + a;
	}

	Int operator ++()
	{
		*this += 1;
		return *this;
	}

	Int operator ++(int)
	{
		Int ans = *this;
		++*this;
		return ans;
	}

	Int operator --()
	{
		*this -= 1;
		return *this;
	}

	Int operator --(int)
	{
		Int ans = *this;
		--*this;
		return ans;
	}

	friend Int operator + (const Int &a, const Int &b)
	{
		if (a.neg() && b.neg()) return -((-a) + (-b));
		if (a.neg() ^ b.neg())
		{
			if (abs(a) < abs(b))
			{
				if (b.neg()) return -(-b - a);
				else return b - (-a);
			}
			else
			{
				if (a.neg()) return -(-a - b);
				else return a - (-b);
			}
		}
		Int ans;
		for (int i = 0; i < max(a.size(), b.size()); i++)
		{
			int ta = i < a.size() ? a[i] : 0;
			int tb = i < b.size() ? b[i] : 0;
			ans[i] += ta + tb;
			ans.push_back(ans[i] / oo);
			ans[i] %= oo;
		}
		while (ans.size() > 1 && ans[ans.size() - 1] == 0) ans.pop_back();
		return ans;
	}

	Int operator -=(const Int &a)
	{
		return *this += -a;
	}

	friend Int operator - (const Int &a, const Int &b)
	{
		if (a.neg() ^ b.neg())
		{
			if (a.neg()) return -(-a + b);
			else return a + (-b);
		}
		if (a.neg() && b.neg()) return -((-a) - (-b));
		if (a < b) return -(b - a);
		Int ans;
		for (int i = 0; i < a.size(); i++)
		{
			ans[i] += a[i] - (i < b.size() ? b[i] : 0);
			ans.push_back(ans[i] < 0 ? -1 : 0);
			ans[i] = (ans[i] + oo) % oo;
		}
		while (ans.size() > 1 && ans[ans.size() - 1] == 0) ans.pop_back();
		return ans;
	}

	friend ostream& operator << (ostream &os, const Int &a)
	{
		if (a.neg()) os << "-";
		os << a[a.size() - 1];
		for (int i = a.size() - 2; i >= 0; i--)
			os << std::setfill('0') << std::setw(4) << a[i];
		return os;
	}

	friend istream& operator >> (istream &is, Int &a)
	{
		string s; is >> s;
		int t = 1, l = s.length(), p = 0;
		a.clear();
		if (s[0] == '-') a.bo = 1, p = 1;
		a.data.push_back(0);
		for (int i = l - 1; i >= p; i--)
		{
			a.data[a.size() - 1] += (s[i] - '0')*t, t *= 10;
			if (t == oo) a.data.push_back(0), t = 1;
		}
		if (a.size() > 1 && a[a.size() - 1] == 0) a.pop_back();
		return is;
	}

	friend Int operator * (const Int &a, const Int &b)
	{
		Int ans;
		for (int i = 0; i < a.size(); i++)
			for (int j = 0; j < b.size(); j++)
			{
				ans[i + j] += a[i] * b[j];
				if (i + j + 1 >= ans.size()) ans.push_back(ans[i + j] / oo);
				else ans[i + j + 1] += ans[i + j] / oo;
				ans[i + j] %= oo;
			}
		while (ans.size() > 1 && ans[ans.size() - 1] == 0) ans.pop_back();
		ans.bo = a.neg() ^ b.neg();
		return ans;
	}

	Int operator *=(const Int &b)
	{
		return *this = (*this)*b;
	}

	friend Int operator / (Int a, const Int &b)
	{
		Int ans; ans.clear();
		if (abs(b) > abs(a)) return 0;
		for (int i = a.size() - b.size(); i >= 0; i--)
		{
			int m = 0;
			for (int k = 13; k >= 0; k--)
			{
				Int t = b * (1 << k);
				if (t.size() > b.size()) t[t.size() - 2] += t[t.size() - 1] * oo, t.pop_back();
				if (a.cmp(t, i)) a.dec(t, i), m += (1 << k);
			}
			if (m) ans.push_back(m);
			if (i + b.size() - 2 >= 0)
			{
				a[i + b.size() - 2] += a[i + b.size() - 1] * oo;
				a[i + b.size() - 1] = 0;
			}
		}
		reverse(ans.data.begin(), ans.data.end());
		ans.bo = a.bo^b.bo;
		return ans;
	}

	Int operator /= (const Int &a)
	{
		return *this = *this / a;
	}

	friend Int operator % (Int a, const Int &b)
	{
		if (abs(b) > abs(a)) return a;
		for (int i = a.size() - b.size(); i >= 0; i--)
		{
			for (int k = 13; k >= 0; k--)
			{
				Int t = b * (1 << k);
				if (t.size() > b.size()) t[t.size() - 2] += t[t.size() - 1] * oo, t.pop_back();
				if (a.cmp(t, i)) a.dec(t, i);
			}
			if (i + b.size() - 2 >= 0)
			{
				a[i + b.size() - 2] += a[i + b.size() - 1] * oo;
				a[i + b.size() - 1] = 0;
			}
		}
		while (a.size() > 1 && a[a.size() - 1] == 0) a.pop_back();
		return a;
	}

	Int operator %=(const Int &a)
	{
		return *this = *this % a;
	}
};

#endif
