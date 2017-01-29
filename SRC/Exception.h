/*
This class allows just creates a message to be printed for Excpetions

Author : Romesh Selvanathan
*/

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

class Exception
{
public:
	/* Constructor */
	Exception(const char* pTxt) : pReason(pTxt) {};
	/* Get Method */
	const char* GetReason(){return pReason;}
private:
	const char* pReason;		// Message
};

#endif