#pragma once
//#include "helper.h"

template<class T>
class IStaticNameObjectList {
public:

	IStaticNameObjectList() {
		AddObject(static_cast<T*>(this));
	}

	virtual ~IStaticNameObjectList() {
		RemoveObject((T*) this);

	}

	static bool AddObject(T* object) {
		DebugLog("StaticNameObjectList Add Name Object List \n\t name = \"%s\" \n\t hash = %x\n", object->GetName().c_str(), object->GetHashCode())
			m_objectList.push_back(object);
		return true;
	}

	static T* Find(std::string name) {
		HASH hash = UT::StringToHash(name);
		for each(auto var in m_objectList) {
			if (hash == var->GetHashCode()) {
				return var;
			}
		}


	}

	static bool RemoveObjectByName(std::string name) {
		auto object = this->Find(name);
		if (object == nullptr) {
			return false;
		}
		RemoveObject(object);
	}

	static bool RemoveObject(T* object) {
		m_objectList.remove(object);
		return true;
	}


	static std::list<T*> m_objectList;
};

#define INSTANTIATE_NAME_OBJ_LIST( type )\
	std::list<type*> IStaticNameObjectList<type>::m_objectList;