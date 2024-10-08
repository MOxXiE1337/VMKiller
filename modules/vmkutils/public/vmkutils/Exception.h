#include <vmkshared/vmk.h>

#ifndef __VMKUTILS_EXCEPTION_H__
#define __VMKUTILS_EXCEPTION_H__

namespace vmkutils
{
	template <typename _EnumType>
	class VMK_API Exception
	{
	public:
		Exception(const std::string& errorMsg, _EnumType id) : m_errorMsg(errorMsg), m_id(id) {}

		virtual std::string what() { return m_errorMsg; }
	protected:
		std::string m_errorMsg;
		_EnumType         m_id;
	};
}

#endif // __VMKUTILS_EXCEPTION_H__
