// RichChain.cpp : 
//

#include "pch.h"
#include <iostream>
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

class Blockchain 
{
private: 
	Block createGenesisBlock();

public:
	vector<Block> chain;

	Blockchain();

	void addBlock(TransactionData tData);
	void isChainValid();

	//contrived example for demo only!!!
	Block *getLatestBlock();

};