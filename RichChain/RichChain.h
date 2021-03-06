// RichChain.cpp : 
//

#include "pch.h"
#include <ctime>

using namespace std;

struct TransactionData {
	double amount;
	string senderKey;
	string receiverKey;
	time_t timestamp;

};

class Block
{
private:
	int index;
	size_t blockHash;
	size_t previousHash;
	size_t generateHash();

public:
	//constructor prototype
	Block(int index, TransactionData tData, size_t previousHash);

	size_t getHash();

	size_t getPreviousHash();

	//data
	TransactionData tData;

	//validate
	bool isHashValid();

};

//constructor
Block::Block(int index, TransactionData tData, size_t prevHash)
{
	this->index = index;
	this->tData = tData;
	this->previousHash = prevHash;
	this->blockHash = generateHash();
}

size_t Block::generateHash()
{
	hash<string> hash1;
	hash<size_t> hash2;
	hash<size_t> finalHash;
	
	string toHash = to_string(tData.amount) + tData.receiverKey + tData.senderKey + to_string(tData.timestamp);

	return finalHash(hash1(toHash) + hash2(previousHash));

}

size_t Block::getHash()
{
	return blockHash;
}

size_t Block::getPreviousHash()
{
	return previousHash;
}

bool Block::isHashValid()
{
	return generateHash() == blockHash;//generate hash should always create same hash
}

class Blockchain 
{
private: 
	Block createGenesisBlock();

public:
	vector<Block> chain;

	Blockchain();

	void addBlock(TransactionData tData);
	bool isChainValid();

	//contrived example for demo only!!!
	Block *getLatestBlock();

};

Blockchain::Blockchain()
{
	Block genesis = createGenesisBlock();
	chain.push_back(genesis);
}

Block Blockchain::createGenesisBlock()
{
	time_t currentTimeStamp;
	TransactionData d;
	d.amount = 0;
	d.receiverKey = "none";
	d.senderKey = "none";
	d.timestamp = time(&currentTimeStamp);

	hash<int> hash1;
	Block genesis(0, d, hash1(0));
	return genesis;

}

Block* Blockchain::getLatestBlock()
{
	return &chain.back();
}

void Blockchain::addBlock(TransactionData data)
{
	int index = (int)chain.size() - 1;
	Block newBlock(index, data, getLatestBlock()->getHash());

}

bool Blockchain::isChainValid()
{
	vector<Block>::iterator iterator;
	int chainLength = (int)chain.size();

	for (iterator = chain.begin(); iterator != chain.end(); ++iterator)
	{
		Block currentBlock = *iterator;
		if (!currentBlock.isHashValid())
		{
			cout << "Invalid Chain! Current block hash is INVALID.";
			return false;
		}

		if (chainLength > 1)
		{
			Block previousBlock = *(iterator - 1);
			if (currentBlock.getPreviousHash() != previousBlock.getHash())
			{
				cout << "Invalid Chain! this block's previous hash not previous block hash.";
				return false;
			}
		}
	}

	return true;
}
