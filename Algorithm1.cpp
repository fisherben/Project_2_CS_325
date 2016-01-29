#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <cstdio>

using std::vector;

// just a large int for initializing purposes
const int largeInt = 999999;

struct coins
{
	int coinAmount;
	int coinValue;
};

//counts the amount of coins used in the vector for the sum.
int coinCounter(vector <struct coins*> resultVector)
{
	int sumCoins;

	for (unsigned int i; i < resultVector.size(); i++)
	{
		sumCoins += resultVector[i]->coinAmount;
	}

	return sumCoins;
}

vector <struct coins*> makeChange(int changeAmount, vector <struct coins*> coinsUsedVector)
{
	vector <struct coins*> resultVector;
	int resultCoins;
	vector <struct coins*> lowestCoinVector;
	int lowestcoins = largeInt;
	int newChangeAmount;

	//basecase
	for (unsigned int i = 0; i < coinsUsedVector.size(); i++)
	{
		if (coinsUsedVector[i]->coinValue == changeAmount)
		{
			coinsUsedVector[i]->coinAmount++;
			printf("Returning with +1 amount to %i\n", coinsUsedVector[i]->coinValue );
			return coinsUsedVector;
		}
	}

	for (unsigned int i = 0; i < coinsUsedVector.size(); i++)
	{
		if (changeAmount > coinsUsedVector[i]->coinValue)
		{
			newChangeAmount = changeAmount - coinsUsedVector[i]->coinValue;
			coinsUsedVector[i]->coinAmount++;
			printf("Calling function with changeAmount %i \n", newChangeAmount);
			resultVector = makeChange(newChangeAmount, coinsUsedVector);
		}

		printf("Comparing resultCoins to lowest coins\n");
		resultCoins = coinCounter(resultVector);
		if (resultCoins < lowestcoins)
		{
			lowestCoinVector = resultVector;
		}
	}

	resultCoins = coinCounter(lowestCoinVector);
	printf("The lowest coin vector is %i \n",  resultCoins);

	printf("returning\n");
	return lowestCoinVector;
}



int main (int argc, const char * argv[])
{
	int changeAmount = 10;
	vector <struct coins*> coinsUsedVector;
	vector <int> coinValues {1, 2 , 5};

	vector <struct coins*> resultVector;
	int resultCoins;

	for (unsigned int i = 0; i < coinValues.size(); i++)
	{
		struct coins *test = new struct coins;
		test->coinAmount = 0;
		test->coinValue = coinValues[i];
		coinsUsedVector.push_back(test);
		printf("pushed coin value %i\n", coinsUsedVector.back()->coinValue);
	}

	resultVector = makeChange(changeAmount, coinsUsedVector);
	resultCoins =coinCounter(resultVector);
	printf("The minimum amount of coins used is: %i\n", resultCoins);
}