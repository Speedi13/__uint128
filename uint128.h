#pragma once
#include <Windows.h>

typedef
struct __uint128
{
	unsigned __int64 LowPart;
	unsigned __int64 HighPart;
	

	__uint128(__int64 init_x64Var) 
    	{
		this->LowPart = init_x64Var;
		this->HighPart = NULL;
    	}
	__uint128& operator=(__uint128 a)
    	{
        LowPart = a.LowPart;
		HighPart = a.HighPart;
        
        return *(__uint128*)this;
    	}
	__uint128 operator+(unsigned __int64 a) //limited to 64-Bits
    	{
		unsigned __int64 bitmask2;
		unsigned __int64 bitmask1;
		bitmask1 = bitmask2 = NULL;

		unsigned __int64 one = 1; //compiler converts that to a 32bit limited o.O
		
		BYTE uebertrag = 0;
		
		for (DWORD i = 0; i < 64; i++)
		{
			bitmask1 = one << i;
			
			BYTE AddBitBit = (a & bitmask1)==bitmask1;
			BYTE CurrentBit = (LowPart & bitmask1)==bitmask1;
			BYTE NewBit = CurrentBit + AddBitBit + uebertrag;

			if ( NewBit == 1 )
			{
				uebertrag = 0;
			}
			else
			if ( NewBit == 2 )
			{
				NewBit = 0;
				uebertrag = 1;
			}
			else
			if ( NewBit == 3 )
			{
				NewBit = 1;
				uebertrag = 1;
			}
			else //error
				uebertrag = 0;

			if ( CurrentBit != NewBit )
			{
				LowPart = LowPart ^ bitmask1;
			}
		}

		for (DWORD i = 0; i < 64; i++)
		{
			bitmask1 = one << i;
			BYTE CurrentBit = (HighPart & bitmask1)==bitmask1;
			BYTE NewBit = CurrentBit + uebertrag;

			if ( NewBit == 1 )
			{
				uebertrag = 0;
			}
			else
			if ( NewBit == 2 )
			{
				NewBit = 0;
				uebertrag = 1;
			}
			else
			if ( NewBit == 3 )
			{
				NewBit = 1;
				uebertrag = 1;
			}
			else //error
				uebertrag = 0;

			if ( CurrentBit != NewBit )
			{
				HighPart = HighPart ^ bitmask1;
			}

		}

		return *this;
    	}
	__uint128 operator+=(unsigned __int64 a)
	{
		*(__uint128*)this = *(__uint128*)this + a;
		return *(__uint128*)this;
	}
	__uint128 operator-(unsigned __int64 a) //limited to 64-Bits
    	{
		unsigned __int64 bitmask1;
		bitmask1 = NULL;

		unsigned __int64 one = 1; //compiler converts that to a 32bit limited o.O
		
		BYTE uebertrag = 0;
		
		for (DWORD i = 0; i < 64; i++)
		{
			bitmask1 = one << i;
			
			BYTE SubBitBit = (a & bitmask1)==bitmask1;
			BYTE CurrentBit = (LowPart & bitmask1)==bitmask1;
			BYTE NewBit = CurrentBit;
			if ( uebertrag == 1 ) //first the "übertrag"
			{
				if ( NewBit == 1 )
				{
					NewBit = 0;
					uebertrag = 0;
				}
				else
				if ( NewBit == 0 )
				{
					NewBit = 1;
					uebertrag = 1;
				}
			}
			if ( SubBitBit == 1 ) //then take care about the actual sub bit
			{
				if ( NewBit == 1 )
					NewBit = 0;
				else
				if ( NewBit == 0 )
				{
					NewBit = 1;
					uebertrag = 1;
				}
			}
			if ( CurrentBit != NewBit )
			{
				LowPart = LowPart ^ bitmask1;
			}
		}

		for (DWORD i = 0; i < 64; i++)
		{
			bitmask1 = one << i;
			BYTE CurrentBit = (HighPart & bitmask1)==bitmask1;

			BYTE NewBit = CurrentBit;
			if ( uebertrag == 1 ) //first the "übertrag"
			{
				if ( NewBit == 1 )
				{
					NewBit = 0;
					uebertrag = 0;
				}
				else
				if ( NewBit == 0 )
				{
					NewBit = 1;
					uebertrag = 1;
				}
			}
			
			if ( CurrentBit != NewBit )
			{
				HighPart = HighPart ^ bitmask1;
			}
		}

		return *this;
    	}
	__uint128 operator-=(unsigned __int64 a)
	{
		*(__uint128*)this = *(__uint128*)this - a;
		return *(__uint128*)this;
	}
	__uint128 operator-(__uint128 a) 
    	{
		unsigned __int64 bitmask;
		bitmask = NULL;
		unsigned __int64 one = 1; //compiler converts that to a 32bit limited o.O
		BYTE uebertrag = 0;
		for (DWORD i = 0; i < 64; i++)
		{
			bitmask = one << i;
			BYTE SubBitBit = (a.LowPart & bitmask)==bitmask;
			BYTE CurrentBit = (LowPart & bitmask)==bitmask;
			BYTE NewBit = CurrentBit;
			if ( uebertrag == 1 ) //first the "übertrag"
			{
				if ( NewBit == 1 )
				{
					NewBit = 0;
					uebertrag = 0;
				}
				else
				if ( NewBit == 0 )
				{
					NewBit = 1;
					uebertrag = 1;
				}
			}
			if ( SubBitBit == 1 ) //then take care about the actual sub bit
			{
				if ( NewBit == 1 )
					NewBit = 0;
				else
				if ( NewBit == 0 )
				{
					NewBit = 1;
					uebertrag = 1;
				}
			}
			if ( CurrentBit != NewBit )
			{
				LowPart = LowPart ^ bitmask;
			}
		}
		for (DWORD i = 0; i < 64; i++)
		{
			bitmask = one << i;
			
			BYTE SubBitBit = (a.HighPart & bitmask)==bitmask;
			BYTE CurrentBit = (HighPart & bitmask)==bitmask;
			BYTE NewBit = CurrentBit;
			if ( uebertrag == 1 ) //first the "übertrag"
			{
				if ( NewBit == 1 )
				{
					NewBit = 0;
					uebertrag = 0;
				}
				else
				if ( NewBit == 0 )
				{
					NewBit = 1;
					uebertrag = 1;
				}
			}
			if ( SubBitBit == 1 ) //then take care about the actual sub bit
			{
				if ( NewBit == 1 )
					NewBit = 0;
				else
				if ( NewBit == 0 )
				{
					NewBit = 1;
					uebertrag = 1;
				}
			}
			if ( CurrentBit != NewBit )
			{
				HighPart = HighPart ^ bitmask;
			}
		}
		return *(__uint128*)this;
	}
	__uint128 operator-=(__uint128 a)
	{
		*(__uint128*)this = *(__uint128*)this - a;
		return *(__uint128*)this;
	}
	__uint128 operator+(__uint128 a) 
    	{
		unsigned __int64 bitmask;
		bitmask = NULL;
		unsigned __int64 one = 1; //compiler converts that to a 32bit limited o.O
		BYTE uebertrag = 0;
		for (DWORD i = 0; i < 64; i++)
		{
			bitmask = one << i;
			
			BYTE AddBitBit = (a.LowPart & bitmask)==bitmask;
			BYTE CurrentBit = (LowPart & bitmask)==bitmask;
			BYTE NewBit = CurrentBit + AddBitBit + uebertrag;
			if ( NewBit == 1 )
			{
				uebertrag = 0;
			}
			else
			if ( NewBit == 2 )
			{
				NewBit = 0;
				uebertrag = 1;
			}
			else
			if ( NewBit == 3 )
			{
				NewBit = 1;
				uebertrag = 1;
				
			}
			else //error
				uebertrag = 0;

			if ( CurrentBit != NewBit )
			{
				LowPart = LowPart ^ bitmask;
			}
		}
		for (DWORD i = 0; i < 64; i++)
		{
			bitmask = one << i;
			
			BYTE AddBitBit = (a.HighPart & bitmask)==bitmask;
			BYTE CurrentBit = (HighPart & bitmask)==bitmask;
			BYTE NewBit = CurrentBit + AddBitBit + uebertrag;
			if ( NewBit == 1 )
			{
				uebertrag = 0;
			}
			else
			if ( NewBit == 2 )
			{
				NewBit = 0;
				uebertrag = 1;
			}
			else
			if ( NewBit == 3 )
			{
				NewBit = 1;
				uebertrag = 1;
			}
			else //error
				uebertrag = 0;


			if ( CurrentBit != NewBit )
			{
				HighPart = HighPart ^ bitmask;
			}
		}
		return *this;
    	}
	__uint128 operator+=(__uint128 a)
	{
		*(__uint128*)this = *(__uint128*)this - a;
		return *(__uint128*)this;
	}
	bool operator==(__uint128 a)
	{
		if ( this->LowPart == a.LowPart && this->HighPart == a.HighPart )
			return true;
		return false;
	}

	bool operator==(unsigned __int64 a)
	{
		if ( this->LowPart == a && this->HighPart == NULL )
			return true;
		return false;
	}

	bool operator!=(__uint128 a)
	{
		if ( this->LowPart != a.LowPart && this->HighPart != a.HighPart )
			return true;
		return false;
	}
	
	DWORD BitsToHex( char* pOutString, bool bDontShowZerosBeforeNumber = true, bool Lower = false );
	DWORD BitsToString( char* pOutString );

} UInt128;
