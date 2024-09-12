#include <vmkshared/vmk.h>

#ifndef __VMKUTILS_NONCOPYABLE_H__
#define __VMKUTILS_NONCOPYABLE_H__

namespace vmkutils
{
	class VMK_API Noncopyable
	{
	public:
		Noncopyable(const Noncopyable&) = delete;
		void operator=(const Noncopyable&) = delete;
	protected:
		Noncopyable() = default;
		~Noncopyable() = default;
	};
}

#endif // __VMKUTILS_NONCOPYABLE_H__
