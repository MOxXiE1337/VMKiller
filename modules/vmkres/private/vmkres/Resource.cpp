#include <vmkres/Resource.h>
#include "ResourcePackageType.h"

namespace vmkres
{
	Resource::Resource(const void* data, size_t size) : m_ref(0), m_lock()
	{
		m_data = new char[size];
		m_size = size;

		if (m_data == nullptr)
			throw vmkutils::Exception("vmkres: Failed to alloc memory", _ResourcePackageError::MEMORY_ALLOC_FAIL);

		memcpy_s(const_cast<void*>(m_data), size, data, size);
	}

	Resource::~Resource()
	{
		delete[] m_data;
	}

	void Resource::lock()
	{
		m_lock.lock();
		m_ref++;
	}

	void Resource::unlock()
	{
		if (m_ref > 0)
		{
			m_lock.unlock();
			m_ref--;
		}
	}

	const void* Resource::data() const
	{
		return m_data;
	}

	size_t Resource::size() const
	{
		return m_size;
	}

	void ResourcePackage::loadResourcePackage(const char* path)
	{
		if (m_loaded)
			throw vmkutils::Exception("vmkres: Resource package is already loaded", _ResourcePackageError::PACKAGE_LOADED);

		std::ifstream file;
		size_t        fileSize = 0;

		file.open(path, std::ios::binary);

		if (!file.is_open())
			throw vmkutils::Exception(std::string("vmkres: Failed to open file ") + path, _ResourcePackageError::FILE_OPEN_FAIL);
	
		// get file size
		file.seekg(std::ios::end);
		fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		// check if it's a resource package (size)
		if(fileSize <= sizeof(ResourcePackageHeader))
			throw vmkutils::Exception(std::string("vmkres: Not a resource package") + path, _ResourcePackageError::NOT_A_RESOURCE_PACKAGE);

		std::unique_ptr<ResourcePackageHeader> package(reinterpret_cast<ResourcePackageHeader*>(new char[fileSize]));

		if(!package)
			throw vmkutils::Exception("vmkres: Failed to alloc memory", _ResourcePackageError::MEMORY_ALLOC_FAIL);

		// read file
		file.read(reinterpret_cast<char*>(package.get()), fileSize);

		// close file
		file.close();

		// check magic
		if(package->Magic != RESOURCE_PACKAGE_TYPE_MAGIC)
			throw vmkutils::Exception(std::string("vmkres: Not a resource package") + path, _ResourcePackageError::NOT_A_RESOURCE_PACKAGE);

		// start parse indices
		uint32_t indicesNum = package->IndicesNum;
		const char* stringTable = reinterpret_cast<const char*>(package.get()) + package->StringTable;
		const char* dataTable = reinterpret_cast<const char*>(package.get()) + package->DataTable;
		
		std::unordered_map<uint32_t, std::string> pathBuilder{};

		for (uint32_t i = 0; i < indicesNum; i++)
		{
			ResourceIndex* resourceIndex = &package->Indices[i];
			
			pathBuilder[resourceIndex->Level] = stringTable + resourceIndex->Name;

			// build path
			std::string resourcePath{};
			for (uint32_t j = 1; j < resourceIndex->Level; j++)
			{
				if (j > 1)
					resourcePath += ".";
				resourcePath += pathBuilder[j];
			}

			// create resource
			try
			{
				m_resources[resourcePath] = std::make_shared<Resource>(dataTable + resourceIndex->Data, resourceIndex->Size);
			}
			catch (vmkutils::Exception<_ResourcePackageError>& exception)
			{
				throw exception; // re throw
			}
		}
	}

	std::shared_ptr<Resource> ResourcePackage::lockResource(const char* resourcePath)
	{
		if (!m_loaded)
			throw vmkutils::Exception("vmkres: Resource package is not loaded", _ResourcePackageError::PACKAGE_NOT_LOADED);

		auto& resource = m_resources.find(resourcePath);

		if (resource == m_resources.end())
			throw vmkutils::Exception(std::string("vmkres: Resource ") + resourcePath + " isn't existed", _ResourcePackageError::RESOURCE_NOT_EXISTED);

		resource->second->lock();
		return resource->second;
	}

	void ResourcePackage::unlockResource(const std::shared_ptr<Resource>& resource)
	{
		if (resource)
			resource->unlock();
	}

	void ResourcePackage::getResources(ResourceList& resourceList)
	{
		if(!m_loaded)
			throw vmkutils::Exception("vmkres: Resource package is not loaded", _ResourcePackageError::PACKAGE_NOT_LOADED);

		for (auto &obj : m_resources)
			resourceList.push_back(obj);
	}

}

