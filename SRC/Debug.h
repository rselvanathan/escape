#ifndef __DEBUG_H__
#define __DEBUG_H__

#define NULL 0

class Debug
{
public:
	static Debug* GetInstance()
	{
		if(mInstance == NULL)
			mInstance = new Debug();
		return mInstance;
	}

	void print();
	void setPrintType(char* type){printType=type;}

	template<typename T>
	void setVar(T v){variable = v;}

private:
	static Debug* mInstance;
	Debug();
	~Debug();

	char* printType;

	//template<typename T>
	//T variable;
}; 

#endif