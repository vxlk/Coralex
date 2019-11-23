#pragma once
#include "basicFunctions.hpp"
#include "basicTypes.hpp"
#include "../guid.h"

namespace lang {

namespace blob {
	class BlobManager;
}
/// todo : typename to enum

/// every type traversing the program is going to do so with a type name attached
/// this is done for easy type comparing
namespace typeKeys {

	constexpr static auto Int         = "Integer";
	constexpr static auto UnsignedInt = "Unsigned Integer";
	constexpr static auto Double      = "Double";
	constexpr static auto Float       = "Float";
	constexpr static auto String      = "String";
	constexpr static auto Function    = "Function";
	constexpr static auto Blob        = "Blob";

	using IntType    = std::pair<std::string, int>;
	using UIntType   = std::pair<std::string, unsigned int>;
	using DoubleType = std::pair<std::string, double>;
	using FloatType  = std::pair<std::string, float>;
	using StringType = std::pair<std::string, std::string>;
	using FuncType   = std::pair<std::string, std::function<void(lang::Blob&)>>;
	using BlobType	 = std::pair<std::string, lang::Blob>;
}

/// a blob represents a piece of user data.  it holds values to an
/// infinite number of states.  Each component within the language is extended
/// from a blob

class Blob final {
public:
	//maybe make the strings enums...
	//                                         //typename     pointer to the type
	using IntList      = std::vector <std::pair<std::string, std::shared_ptr<int>>>;
	using UIntList     = std::vector <std::pair<std::string, std::shared_ptr<unsigned int>>>;
	using DoubleList   = std::vector <std::pair<std::string, std::shared_ptr<double>>>;
	using FloatList    = std::vector <std::pair<std::string, std::shared_ptr<float>>>;
	using StringList   = std::vector <std::pair<std::string, std::shared_ptr<std::string>>>;
	using BlobList	   = std::vector <std::pair<std::string, std::shared_ptr<Blob>>>;
	//                                         
	using FunctionList = std::vector <std::pair<std::string, //typename 
									  std::vector<std::pair<std::string, //list of function names 
							          std::function<void(Blob&)>>>>>;  //list of functions

	static std::string&&  toString();
	static Blob&&		  fromString(const std::string&);

	static Blob&&		  castData(const std::string& name, const std::string& type, const std::string& newType);

	// accessing a typeKey from the blob
	typeKeys::IntType    getInt(const std::string& varName);
	typeKeys::UIntType   getUInt(const std::string& varName);
	typeKeys::DoubleType getDouble(const std::string& varName);
	typeKeys::FloatType  getFloat(const std::string& varName);
	typeKeys::StringType getString(const std::string& varName);
	typeKeys::BlobType   getBlob(const std::string& varName);
	
	// called from render loop on every blob in the scene
	void		  runFunctions(Blob&);

	// accessing data from the blob directly (if it doesn't need organized/displayed)
	template <typename T>
	std::vector<T> Get();
	template <typename T>
	std::vector<T> Get(const std::string& varName);
	template <typename T>
	T Get();
	template <typename T>
	T Get(const std::string& varName);

	constexpr const Guid& GetID() { return this->blobID; }

	//todo: ctors write to blob db

	// default id
	Blob();
	// from id
	Blob(Guid id);
	// from name
	Blob(const std::string& name);

	
private:

	bool isEqual(const Blob& other);
	Blob&& construct(const Blob& other);

	//has a unit of every possible type
	IntList      ints;
	UIntList     uints;
	DoubleList   doubles;
	FloatList    floats;
	StringList   strings;
	FunctionList funcs;
	BlobList	 blobs;

	std::string  blobName;
	Guid blobID;
};

namespace blob {
	//accessing a blob by name or id from memory
	template <typename T>
	std::vector<T> Get(const std::string& blobName);
	template <typename T>
	T Get(const std::string& blobName);
	template <typename T>
	std::vector<T> Get(const Guid& id);
	template <typename T>
	T Get(const Guid& id);

	// owner of all blobs loaded in the scene
	class BlobManager {
		std::vector<lang::Blob> activeBlobs;
		// todo: on load read blob database
		BlobManager();
		// todo: on destroy write to blob database
		~BlobManager();
	public:
		BlobManager& Instance() {
			static BlobManager b;
			return b;
		}
	};
}
}//namespace lang