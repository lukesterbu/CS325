#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// Function prototypes
void printVector(vector<int> itemWeight);
int firstFit(vector<int> itemWeight, int binCap, int numItem);
int firstFitDecreasing(vector<int> itemWeight, int binCap, int numItem);
int bestFit(vector<int> itemWeight, int binCap, int numItem);

int main()
{
	srand(time(0));
	int testCases = 20;
	int binCap = 10;
	int numItems = 10;
	
	for (int test = 0; test < testCases; test++)
	{
		vector<int> itemWeights;
		for (int i = 0; i < numItems; i++)
		{
			itemWeights.push_back(rand() % 10 + 1);
		}
		// Print out test case vector
		cout << "Test " << test + 1 << ": ";
		printVector(itemWeights);
		// Call functions here
		cout << "Test Case " << test + 1 << " First Fit: " << firstFit(itemWeights, binCap, numItems);
		cout << ", First Fit Decreasing: " << firstFitDecreasing(itemWeights, binCap, numItems);
		cout << ", Best Fit: " << bestFit(itemWeights, binCap, numItems) << endl << endl;
	}
}

/* Put each item as you come to it into the first (earliest opened)
 ** bin into which it fits. If there is no available bin then open a
 ** new bin. */
int firstFit(vector<int> itemWeight, int binCap, int numItem) {
	int numBins = 0;
	int binCapCopy[numItem];
	
	for (int i = 0; i < numItem; i++)
	{
		int x;
		for (x = 0; x < numBins; x++)
		{
			if (binCapCopy[x] >= itemWeight[i])
			{
				binCapCopy[x] -= itemWeight[i];
				break;
			}
		}
		if (x == numBins)
		{
			binCapCopy[numBins] = binCap - itemWeight[i];
			numBins++;
		}
	}
	return numBins;
}

/* First sort the items in decreasing order by size, then use
 ** First-Fit on the resulting list. */
int firstFitDecreasing(vector<int> itemWeight, int binCap, int numItem) {
	// Copy the array so best fit doesn't get affected
	vector<int>sortedItemWeight = itemWeight;
	// Sort the vector in descending order
	sort(sortedItemWeight.begin(), sortedItemWeight.end(), std::greater<int>());
	return firstFit(sortedItemWeight, binCap, numItem);
}

/*  Place the items in the order in which they arrive. Place the
 ** next item into the bin which will leave the least room left
 ** over after the item is placed in the bin. If it does not fit
 ** in any bin, start a new bin. */
int bestFit(vector<int> itemWeight, int binCap, int numItem) {
	int numBins = 0;
	int binCapCopy[numItem];
	
	for (int i = 0; i < numItem; i++)
	{
		int minBinCap = binCap;
		int binIndex = 0;
		for (int x = 0; x < numBins; x++)
		{
			// Bin capacity is greater than the current item's weight and
			// bin capacity minus the current item's weight is less than the
			// capacity of the bin with the minimum capacity
			if (binCapCopy[x] >= itemWeight[i] && binCapCopy[x] - itemWeight[i] <= minBinCap)
			{
				binIndex = x;
				minBinCap = binCapCopy[x] - itemWeight[i];
			}
		}
		if (minBinCap == binCap) // Current smallest capacity equals bin capacity
		{
			binCapCopy[numBins] = binCap - itemWeight[i];
			numBins++;
		}
		else
			binCapCopy[binIndex] -= itemWeight[i];
	}
	return numBins;
}


// For testing
void printVector(vector<int> itemWeight)
{
	vector<int>::iterator iter;
	for (iter = itemWeight.begin(); iter != itemWeight.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
}
