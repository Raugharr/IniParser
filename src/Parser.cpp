/*
 * File: Parser.cpp
 * Author: David Brotz
 */
#include "Parser.h"

#include <string.h>
#include <assert.h>

/*
 * @brief Fills _NameSize with the size of each _NameCt null terminated string in _NameBuff.
 */
void NameSize(const char* _NameBuff, int* _NameSize, int _NameCt) {
	const char* _NamePtr = _NameBuff;
	
	if(_NameBuff == NULL || _NameSize == NULL)
		return;
	
	for(int i = 0; i < _NameCt; ++i) {
		_NameSize[i] = strlen(_NamePtr);
		_NamePtr += _NameSize[i] + 1;
	}
}

/*
 * @brief Continously increments the pointer _Ptr until the character _Key is found.
 */
void SkipAfter(char** _Ptr, char _Key) {
	while(**_Ptr != _Key) {
		if(**_Ptr == '\0')
			return;
		++(*_Ptr);
	}
	++(*_Ptr);
}

Parser::Parser(char* _Buffer) : m_Ini(_Buffer) {

}

Parser::~Parser() {

}

int Parser::GetKeys(const char* _Section, const char* _NameBuff, int _NameCt) {
	int _Write = 0;
	int _SecLen = strlen(_Section);
	
	if(m_Ini == NULL || _Section == NULL || _NameBuff == NULL)
		return 0;
	NameSize(_NameBuff, _NameLen, _NameCt);
	if(_Section != NULL) {
		while(true) {
			while(*m_Ini != '[') {
				if(*m_Ini == '\0')
					return 0;
				else if(*m_Ini == ';')
					SkipAfter(&m_Ini, '\n');
				++m_Ini;
			}
			if(!strncmp(m_Ini + 1, _Section, _SecLen)) {
				m_Ini += _SecLen + 1;
				assert(*(m_Ini - 1) != ']');
				SkipAfter(&m_Ini, ']');
				break;
			}
			SkipAfter(&m_Ini, ']');
		}
	}
	for(int i = 0; i < _NameCt; ++i) {
		_Write += GetKey(_NameBuff, _NameLen, _NameCt); 
	}		 
	return _Write;
}

int Parser::GetKey(const char* _NameBuff, const int* _NameLen, int _NameCt) {
	int _Len = 0;

	SkipWhitespace(&m_Ini);
	for(int i = 0; i < _NameCt; ++i) {
		_Len = _NameLen[i] - _NameLen[0];
		if(!strncmp(_NameBuff + _Len, m_Ini, _NameLen[i])) {
			m_Ini += _Len;
			SkipAfter(&m_Ini, '=');
			SkipWhitespace(&m_Ini);
			//_Len -= m_KeyBuff;
			while(m_KeyNum < m_KeySize && *m_Ini == '\0') {
				m_KeyBuff[m_KeyNum] = *m_Ini;
				++m_KeyNum;
				++m_Ini;
			}
		}
	}
	return _Len;
}

/*
 * @brief Continuously increments the pointer _Ptr until an uncommented letter if found.
 */
void Parser::SkipWhitespace(char** _Ptr) {
	while(**_Ptr <= ' ') {
		if(**_Ptr == '\0')
			 return;
		else if(**_Ptr == ';')
			SkipAfter(_Ptr, '\n');
		++(*_Ptr);
	}
}
