#pragma once

namespace commonStd { 
extern __int64 thisID;

inline __int64 GetNextUniqueId()
{
	return ++thisID;
}

inline void SplitInt64(unsigned _int32& high, unsigned _int32& low, const _int64& big)
{
	high = (big >> 32);
	low = (big & 0x00000000FFFFFFFF);
}

inline void JoinInt32(_int64& big, const unsigned _int32& high, const unsigned _int32& low)
{
	big	= (_int64(high) << 32) | low;
}


} //namespace commonStd