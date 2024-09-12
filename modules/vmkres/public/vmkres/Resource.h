#include <vmkshared/vmk.h>
#include <vmkutils/Noncopyable.h>
#include <vmkutils/Exception.h>

#ifndef __VMKRES_RESOURCE_H__
#define __VMKRES_RESOURCE_H__

namespace vmkres
{
	enum class _ResourcePackageError
	{
		PACKAGE_LOADED,
		PACKAGE_NOT_LOADED,
		FILE_OPEN_FAIL,
		FILE_READ_FAIL,
		NOT_A_RESOURCE_PACKAGE,
		RESOURCE_NOT_EXISTED,
		MEMORY_ALLOC_FAIL,
	};

	class VMK_API Resource
	{
	private:
		friend class ResourcePackage;

		std::atomic_int m_ref;
		std::mutex  m_lock;
		const void* m_data;
		size_t      m_size;

		void lock();
		void unlock();
	public:
		Resource(const void* data, size_t size);
		~Resource();

		const void* data() const;
		size_t size() const;
	};

	using ResourceList = std::list< std::pair<std::string, std::shared_ptr<Resource>>>;

	class VMK_API ResourcePackage : public vmkutils::Noncopyable
	{
	private:
		bool m_loaded;
		std::unordered_map<std::string, std::shared_ptr<Resource>> m_resources;
	public:
		void                      loadResourcePackage(const char* path);
		std::shared_ptr<Resource> lockResource(const char* resourcePath);
		void                      unlockResource(const std::shared_ptr<Resource>& resource);

		void                      getResources(ResourceList& resourceList);
	};
}

#endif // __VMKRES_RESOURCE_H__
