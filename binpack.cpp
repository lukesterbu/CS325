//
//  binpack.cpp
//  binpack
//
//  Created by Luke Burris on 3/7/19.
//  Copyright © 2019 Luke Burris. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::vector;
using std::stringstream;
using std::ifstream;
using std::string;

// Function Prototypes
int firstFit(vector<int> itemWeight, int binCap, int numItem);
int firstFitDecreasing(vector<int> itemWeight, int binCap, int numItem);
int bestFit(vector<int> itemWeight, int binCap, int numItem);

int main(int argc, const char * argv[]) {
	// Variable declarations
	string line; // used for stringstreams
	int num = 0;
	int testCases = 0;
	int binCap = 0;
	int numItem = 0;
	vector<int> itemWeights;
	
	ifstream myInputFile("/Users/burrisl/Downloads/bin2.txt");
	if (myInputFile.is_open())
	{
		stringstream row;
		if (getline(myInputFile, line))
		{
			stringstream row(line);
			if (row >> num)
				testCases = num;
			for (int i = 0; i < testCases; i++)
			{
				// 3 lines of input for each test case
				for (int x = 0; x < 3; x++)
				{
					if (getline(myInputFile, line))
					{
						stringstream row(line);
						if (row >> num)
						{
							if (x == 0)
								binCap = num;
							if (x == 1)
								numItem = num;
							if (x == 2)
							{
								for (int y = 0; y < numItem; y++)
								{
									itemWeights.push_back(num);
									row >> num;
								}
							}
						}
					}
				}
				cout << "Test Case " << i + 1 << " First Fit: " << firstFit(itemWeights, binCap, numItem);
				cout << ", First Fit Decreasing: " << firstFitDecreasing(itemWeights, binCap, numItem);
				cout << ", Best Fit: " << bestFit(itemWeights, binCap, numItem) << endl;
				for (int n = 0; n < numItem; n++)
				{
					itemWeights.erase(itemWeights.begin());
				}
			}
		}
	}
	else
		cout << "The file bin.txt does not exist in this directory." << endl;

	return 0;
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
