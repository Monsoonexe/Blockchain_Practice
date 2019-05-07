#include "pch.h"
#include "RichChain.h"

int main()
{
	std::cout << "Hello Blockchain!\n";

	Blockchain blockChain_RichCoin;

	//first added block
	TransactionData data1;
	time_t data1Time;
	data1.amount = 1.5f;
	data1.receiverKey = "Monsoonexe";
	data1.senderKey = "BriZi";
	data1.timestamp = time(&data1Time);

	blockChain_RichCoin.addBlock(data1);
	cout << "Chain is Valid: " << blockChain_RichCoin.isChainValid() << endl;
	cout << blockChain_RichCoin.getLatestBlock()->getHash();
}