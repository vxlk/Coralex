#pragma once
#include <vector>
#include <string>

namespace lang {
	class Blob;
}

namespace db {

// A Subtransaction represents one job that can be prepared for the database
template <class TransactionType>
class SubTransaction {
public:
	enum class Type {
		eUpdate,
		eQuery,
		eAdopt,
		eCreate,
		eDestroy
	};
};

// Transaction Interface
// A transaction represents an asynchronous query to the database
// this means all subtransactions within a transaction either succeed or fail
// there can be different kinds of transactions for different objects

class ITransaction {
public:

	using subTransactionList_t = std::vector<SubTransaction<ITransaction>>;
	virtual bool Create (const lang::Blob) = 0;
	virtual bool Destroy(const lang::Blob) = 0;
	virtual bool Update (const lang::Blob) = 0;
	virtual bool Adopt  (const lang::Blob) = 0;
	virtual bool Query  (const std::string& name);
protected:
	subTransactionList_t m_subTransactions;
};
} //namespace db