#include<iostream>
using namespace std;
#include<string.h>
#include<assert.h>
#include<stdio.h>
#define MAX_SIZE 4294967291

class String
{
public:
	typedef char* Iterator;
	typedef const char* Const_Iterator;
	//1.构造函数
	String()
		:_capacity(10)
		,_size(0)
	{
		_str = new char[_capacity+1];
	}
	//2.带参数构造函数构造
	String(const char* str)
		:_capacity(strlen(str))
		,_size(strlen(str))
	{
		if(str == NULL)
			str = " ";
		_str = new char[strlen(str)];
		strcpy(_str,str);
	}
	//3.拷贝char*类型的字符串的前n个构造
	String(const char* str,size_t n)
	{
		size_t len = strlen(str);
		if(n>len)
			n = len;
		_str = new char[n+1];
		strncpy(_str,str,n);
		_str[n+1] = '\0';
		_size = n;
		_capacity = n;
	}
	//4.用string中的某一段
	String(const String& str, size_t pos,size_t n = npos)
	{
		assert(pos<str._size);
		int len = str._size-pos;
		if((int)n == -1)
			n = len;
		if(n>len)
			n = len;
		_str = new char[n+1];
		strncpy(_str,str._str+pos,n);
		_size=n;
		_capacity=n;
		_str[n+1] = '\0';
	}
	//5.拷贝构造
	String(const String& str)
		:_str(new char[str._size+1])
		,_size(str._size)
		,_capacity(str._size)
	{
		strcpy(_str,str._str);
	}
	//6.赋值运算重载
	String& operator = (const String& str)
	{
		if(this != &str)
		{
			char* ptr = new char[str._size+1];
			strcpy(ptr,str._str);
			delete[] _str;
			_str = ptr;
			_size = str._size;
			_capacity = str._capacity;
		}
		return *this;
	}
	
	~String()
	{
		if(_str != NULL)
		{
			delete[] _str;
			_str = NULL;
			_size = 0;
			_capacity = 0;
		}
	}
	////////////////////////以下是迭代器的实现 /////////////////////////////
	Iterator Begin()
	{
		return _str;
	}
	Const_Iterator cBegin() const
	{
		return _str;
	}
	Iterator End()
	{
		return _str+_size;
	}
	Const_Iterator cEnd() const
	{
		return _str+_size;
	}
	Iterator rBegin()
	{
		return End();
	}
	Iterator rEnd()
	{
		return Begin()-1;
	}
	////////////////////元素访问//////////////////////
	//[]访问字符串的某个字符
	char& operator[](size_t pos)
	{
		assert(pos<_size);
		return _str[pos];
	}
	const char& operator[](size_t pos)const
	{
		assert(pos<_size);
		return _str[pos];
	}
	///////////////////size&capacity//////////////////
	size_t Size() const
	{
		return _size;
	}
	size_t Max_Size() const
	{
		return MAX_SIZE;
	}
	size_t Length() const
	{
		return _size;
	}
	size_t Capacity() const
	{
		return _capacity;
	}
	void Resize(size_t size,char ch = char())
	{
		if(size>_capacity)
		{
			char* ptr = new char[size+1];
			strcpy(ptr,_str);
			delete[] _str;
			_str = ptr;
			_capacity = size;

		}
		if(size<=_size)
			_size = size;
		else
		{
			
			while(_size<size)
			{
				_str[_size++] = ch;
			}
			_str[_size] = ch;
			
		}
		_str[_size+1] = '\0';
	}
		
	/////////////////string操作接口///////////////////
	//1.在字符串末尾插入入一个字符
	void Push_Back(char ch)
	{
		if(_size == _capacity)
		{
			_capacity = 2*_capacity+3;
			char* str = new char[_capacity+1];
			strcpy(str,_str);
			str[_size] = ch;
			_size++;
			str[_size] = '\0';
			delete[] _str;
			_str = str;
		}
		else
		{
			_str[_size] = ch;
			_size++;
			_str[_size] = '\0';
		}
	}
	//2.在字符串后面添加一个字符串
	void Push_Back(const char* str)
	{
		int len = _size+strlen(str);
		if(_capacity-_size>strlen(str))
		{
			strcat(_str,str);
			_size = len;
		}
		else
		{
			char* ptr = new char[len+1];
			strcpy(ptr,_str);
			strcat(ptr,str);
			delete[] _str;
			_str = ptr;
			_size=len;
			_capacity=len;
		}
	}
	
	//方便调试的打印
	void print()
	{
		cout<<"capacity:"<<_capacity<<endl;
		cout<<"size:"<<_size<<endl;
		cout<<"_str:"<<_str<<endl;
	}
	/////////////////////////////输入输出重载//////////////////////
	friend ostream& operator<<(ostream& _cout,const String& str)
	{
		return _cout<<str._str;
	}
	friend istream& operator>>(istream& _cin,String& str)
	{
		String temp;
		char ch;
		while((ch=getchar()) != '\n')
		{
			temp.Push_Back(ch);
		}
		swap(temp._str,str._str);
		swap(temp._capacity,str._capacity);
		swap(temp._size,str._size);
	}
private:
	char* _str;
	size_t _size;
	size_t _capacity;
	const static size_t npos;
};
const size_t String::npos = -1;
//1.构造及赋值运算符重载的测试
void test_construct()
{
	//有参数构造函数
	String s("122");
	//无参构造函数
	String s1;
	//拷贝构造
	String s2(s);
	//赋值运算符重载
	s1 = s2;
	s1.print();
	s1 = "1233455566";
	//用cstring的前n个构造
	String s3("12345",4);
	String s4("123",4);
	//用字符串中的某一段构造
	String s5(s3,1,2);
	String s6(s3,2,3);
	s.print();
	s1.print();
	s2.print();
	s3.print();
	s4.print();
	s5.print();
	s6.print();
	String ::Const_Iterator it = s1.cBegin();
	while(it != s1.cEnd())
	{
		cout<<*it++;
	}
	cout<<endl;
	it = s1.rBegin();
	while(it != s1.rEnd())
	{
		cout<<*(it--);
	}
	cout<<endl;
}
//2.测试Size()、Length()、Capacity()接口对string的操作
void test_string_op()
{
	//1.测试length size capacity
	String s;
	s = "123344";
	//1.测试追加一个字符
	cout<<"s:size():"<<s.Size()<<endl;
	cout<<"s:length():"<<s.Length()<<endl;
	cout<<"s:capacity():"<<s.Capacity()<<endl;
	s.Push_Back('9');
	cout<<"s:size():"<<s.Size()<<endl;
	cout<<"s:length():"<<s.Length()<<endl;
	cout<<"s:capacity():"<<s.Capacity()<<endl;
	cout<<"s:MAX_SIZE:"<<s.Max_Size()<<endl;
	s.print();
	//2.测试追加一个串
	s.Push_Back("1");
	cout<<"s:size():"<<s.Size()<<endl;
	cout<<"s:length():"<<s.Length()<<endl;
	cout<<"s:capacity():"<<s.Capacity()<<endl;
	s.print();
	s.Push_Back("123355555");
	cout<<"s:size():"<<s.Size()<<endl;
	cout<<"s:length():"<<s.Length()<<endl;
	s.print();
	//3.测试resize
	s.Resize(20);
	s.print();
	s.Resize(23,'C');
	
	String ::Const_Iterator it = s.cBegin();
	while(it != s.cEnd())
	{
		cout<<*it++;
	}
}
//3.测试operator<<、operator>>
void test_oper()
{
	String s;
	cin>>s;
	cout<<s<<endl;
	s.print();
}
int main()
{
	//test_construct();
	//test_string_op();
	test_oper();
}
