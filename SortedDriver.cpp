// SortedDriver.cpp
// Ryan Durnan
// COSC 2030
// Lab6
// 5 Nov 2018

#include "stdafx.h"

#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	if (number.empty())			// If the vector is empty, then there is no "most isolated entry."
	{
		return 0;
	}
	if (number.size() == 1)		// If the vecotr only has one entry, just return that entry.
	{
		return number[0];
	}
	double maxDist;		// Keep track of the maximum distance between entries
	double mostIso;		// Keep track of the most isolated entry
	double currDist;	// Keep track of the current distance between entries
	double leftDist;	// Keep track of the distance between current and previous entries
	double rightDist;	// Keep track of the distance between current and next entries
	for (int i = 0; i < number.size(); i++)
	{
		if (i == 0)		// On the first loop...
		{
			maxDist = abs(number[0] - number[1]);	// Maximum distance is the absolute value of the difference between the first and second entries
			mostIso = number[0];					// Most isolated entry is the first entry
		}
		else if (i+1 == number.size())		// If the loop has reached the end...
		{
			currDist = abs(number[i] - number[i - 1]);	// Current distance is equal to the difference between the last and second to last entries
			if (currDist > maxDist)		// Check if the current distance is greater than the maximum distance
			{
				maxDist = currDist;		// Update maximum distance
				mostIso = number[i];	// Update most isolated entry
			}
		}
		else
		{	// If the loop is in the middle of the vector...
			leftDist = abs(number[i] - number[i - 1]);	// Track the distance between the current and previous entries
			rightDist = abs(number[i] - number[i + 1]);	// Track the distance between the current and next entries
			if (leftDist > rightDist)		// Check if the left distance is greater than the right distance
			{
				if (rightDist > maxDist)	// Check if the right distance is greater than the maximum distance
				{
					maxDist = rightDist;	// Update maximum distance
					mostIso = number[i];	// Update most isolated entry
				}
			}
			if (rightDist > leftDist)		// Check if the right distance is greater than the left distance
			{
				if (leftDist > maxDist)		// Check if the left distance is greater than the maximum distance
				{
					maxDist = leftDist;		// Update maximum distance
					mostIso = number[i];	// Update most isolated entry
				}
			}
		}
	}

	return mostIso;	// Return most isolated entry
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	if (A.empty())			// If A has no items, then there are no items to check for occurance in B. Just return 0.
	{
		return 0;
	}
	if (B.empty())			// If B has no items, then none of the items in A occur in B. Just return the number of elements in A.
	{
		return A.size();
	}
		
	int inB = 0;		// Keep track of the number of items that occur in A and B.
	bool found = false;	// Used to determine if a number has been found

	for (list<string>::iterator itA = A.begin(), itB = B.begin(); itA != A.end() && itB != B.end(); itA++)
	{
		while (found == false)		// If the number has not yet been found...
		{
			if (itB == B.end())		// Check if iterator B has reached its end
			{
				break;				// Exit the loop if necessary
			}
			else if (*itB > *itA)	// Check if iterator B has surpassed iterator A
			{
				break;				// Exit the loop if necessary
			}
			else
			{
				if (*itA == *itB)	// Check if iterator A's current value is equal to iterator B's current value
				{
					inB++;			// Increment number of items that occur in A and B if necessary
					found = true;	// Indicate that the desired number has been found so the loop can exit
				}
				else
				{
					itB++;			// Increment iterator B if its current value does not equal iterator A's current value
				}
			}
		}
		found = false;	// Reset variable that determines if number has been found. I need this so the previous while-loop applies for every value of iterator A
	}

	return (A.size() - inB);	// Return the difference between the size of A and the number of elements that show up in both A and B.
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
