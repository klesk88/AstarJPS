#pragma once

#define NON_COPYABLE_CLASS(ClassName) \
private: \
	ClassName( const ClassName& ) = delete; \
	ClassName& operator=( const ClassName& ) = delete;