/*
 * Author: David Brotz
 * File: Parser.h
 */

#ifndef __PARSER_H
#define __PARSER_H

class Parser {
public:
	Parser(char* _Buffer);
	~Parser();

	int GetKeys(const char* _Section, const char* _NameBuff, int _NameCt);
	/**
	 * @brief Adds an internal structure that will remember the pending changes. 
		This method does not actually change the file, use Flush() to add the changes.
	 * @arg _Section The section this key will be under.
	 * @arg _Name Name of the key.
	 * @arg _Value Value of the key.
	 * @return Number of bytes appended.
	*/
	int AddKey(const char* _Section, const char* _Name, const char* _Value);
	int ChangeKey(const char* _Section, const char* _Name, const char* _Value);
	int RemoveKey(const char* _Section, const char* _Name, const char* _Value);
	void Flush();
private:
	int GetKey(const char* _NameBuff, const int* _NameLen, int _NameCt);
	void SkipWhitespace(char** _Ptr);

	static const int m_KeySize = 512;

	char m_KeyBuff[m_KeySize];
	int m_KeyNum;
	char* m_Ini;
};

#endif
