#pragma once

namespace commonStd {

template<typename T> 
void SafeDelete( T *& t)
{
	if ( t != nullptr )
	{
		delete t;
		t = nullptr;
	}
}

template<typename T> 
void SafeDeleteArray( T t[])
{
	if ( t != nullptr )
	{
		delete t;
		t = nullptr;
	}
}

template<typename T> 
void SafeDeleteHandle( T t[])
{
	if ( t != nullptr )
	{
		DeleteObject(t);
		t = nullptr;
	}
}

} // namespace commonStd