#pragma once

/// includes
#include <memory>
#include <string>

/// defines
#define TPGE_OBJECT(className, baseClassName)							\
	virtual std::string GetTypeName() { return #className; }			\
	static std::string GetTypeNameStatic() { return #className; }		\
	static std::string GetBaseTypeNameStatic() { return #baseClassName; }\
	static baseClassName* Create(std::shared_ptr<TPGEContext> context)	\
		{																\
			return new className(context);								\
		}
#define TPGE_BASE_OBJECT(className)										\
	virtual std::string GetTypeName() { return #className; }			\
	static std::string GetTypeNameStatic() { return #className; }		

namespace TPGE
{
	class TPGEContext;

	class TPGEObject
	{
	public:
		TPGE_BASE_OBJECT(TPGEObject)

		TPGEObject(std::shared_ptr<TPGEContext> context);
		~TPGEObject();

	protected:
		/// The context reference
		std::shared_ptr<TPGEContext> context_;

	private:
	};
}