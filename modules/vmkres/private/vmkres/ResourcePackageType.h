#include <vmkshared/vmk.h>

#ifndef __VMKRES_RESOURCE_PACKAGE_TYPE_H__
#define __VMKRES_RESOURCE_PACKAGE_TYPE_H__

namespace vmkres
{
	constexpr uint32_t RESOURCE_PACKAGE_TYPE_MAGIC = 'VRES';

	struct ResourceIndex
	{
		uint32_t Level;
		uint32_t Name; // RA from string table
		uint32_t Data; // RA from data table
		uint32_t Size; 
	};

	struct ResourcePackageHeader
	{
		uint32_t      Magic;
		uint32_t      StringTable;
		uint32_t      DataTable;
		uint32_t      IndicesNum;
		ResourceIndex Indices[];
	};
}

#endif // __VMKRES_RESOURCE_PACKAGE_TYPE_H__
