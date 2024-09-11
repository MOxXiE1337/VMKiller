#include <vmkshared/vmk.h>

#ifndef __VMKUTILS_EXCEPTION_H__
#define __VMKUTILS_EXCEPTION_H__

namespace vmkutils
{
	class VMK_API Exception
	{
	public:
		Exception(const std::string& errorMsg, int id) : m_errorMsg(errorMsg), m_id(id) {}
	
		virtual std::string what() { return m_errorMsg; }
	protected:
		std::string m_errorMsg;
		int         m_id;
	};
}

#endif // __VMKUTILS_EXCEPTION_H__
