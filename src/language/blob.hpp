#pragma once
#include "basicFunctions.hpp"
#include "basicTypes.hpp"

namespace lang {

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

	typeKeys::IntType    getInt(const std::string& varName);
	typeKeys::UIntType   getUInt(const std::string& varName);
	typeKeys::DoubleType getDouble(const std::string& varName);
	typeKeys::FloatType  getFloat(const std::string& varName);
	typeKeys::StringType getString(const std::string& varName);
	typeKeys::BlobType   getBlob(const std::string& varName);
	
	// called from render loop on every blob in the scene
	void		  runFunctions(Blob&);

private:
	//has a unit of every possible type
	IntList      ints;
	UIntList     uints;
	DoubleList   doubles;
	FloatList    floats;
	StringList   strings;
	FunctionList funcs;
	BlobList	 blobs;

	std::string  blobName;
};
}//namespace lang