#include "uint128.h"

DWORD __uint128::BitsToHex( char* pOutString, bool bDontShowZerosBeforeNumber, bool Lower )
{
	char A = 'A';
	if ( Lower == true )
		A = 'a';

	DWORD dwCharPos = NULL;
	DWORD dwBitCount = sizeof(__uint128); //16 Byte
	DWORD dwCurrentSubBit = 8;
	bool bOnlyZerosYet = true;
	for (int j = dwBitCount-1; ; j--)
	{
		BYTE* pValue = (BYTE*)(void*)( (DWORD_PTR)this + j );

		if ( *(BYTE*)pValue != NULL && bOnlyZerosYet == true )
		{
			bOnlyZerosYet = false;
		}
		if ( bOnlyZerosYet == true && bDontShowZerosBeforeNumber == true )
			goto l_continue;
		BYTE valueLower = *(BYTE*)pValue & 0x0F;
		BYTE valueUpper = (*(BYTE*)pValue & 0xF0) >> 4;
		char _char = NULL;
		_char = valueUpper + '0';
		if ( _char > '9' )
			_char = valueUpper + A - 10;
		pOutString[dwCharPos] = _char;
		dwCharPos++;

		_char = valueLower + '0';
		if ( _char > '9' )
			_char = valueLower + A - 10;
		pOutString[dwCharPos] = _char;
		dwCharPos++;
l_continue:	
		if (j == 0)
			break;
	}
	pOutString[dwCharPos] = NULL;
	return dwCharPos;
}

DWORD __uint128::BitsToString( char* pOutString )
{
	void* pNumber = this;
	DWORD dwBitCount = sizeof(__uint128); //16 Byte

	DWORD bitmask = NULL;
	DWORD dwCurrentSubBit = 8;
	DWORD dwOne = 1;
	DWORD dwCharPos = NULL;
	pNumber = (void*)( (DWORD_PTR)pNumber + (dwBitCount-1) );
	BYTE NumberPart = *(BYTE*)pNumber;
	for (DWORD i = (dwBitCount*8); i > 0 ; i--)
	{
		dwCurrentSubBit--;
		bitmask = dwOne << dwCurrentSubBit;
		bool CurrentBit = (NumberPart & bitmask)==bitmask;
		pOutString[dwCharPos] = ( CurrentBit==true ? '1' : '0' ); 
		dwCharPos++;

		if ( dwCurrentSubBit == 0 )
		{
			pNumber = (void*)( (DWORD_PTR)pNumber - 1 );
			NumberPart = *(BYTE*)pNumber;
			dwCurrentSubBit = 8;
		}
	}
	pOutString[dwCharPos] = NULL;
	return dwCharPos;
}