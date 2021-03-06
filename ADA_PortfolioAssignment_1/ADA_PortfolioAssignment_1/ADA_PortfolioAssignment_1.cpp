// ADA_PortfolioAssignment_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BinarySearchTree.h"
#include "Stopwatch.h"
#include "ConsoleMatrix.h"

using namespace std;

const int N = 100000;
const int n = 11;
const int randN = 2000;
const int threads = 4;

std::vector<int> fib(size_t N);

int main()
{
	int vals[] = { 9, 21 };

	cout << "ASSIGNMENT 1:" << endl;
	cout << "Index tree of size " << n << ":" << endl;

	BinarySearchTree smallerTree(n, 5);
	smallerTree.print();

	for (int i = 0; i < 2; i++) cout << "Tree contains " << vals[i] << ": " << smallerTree.contains(vals[i]) << endl;

	cout << endl << "Vector tree of size " << n << ", based on the fibonacci sequence:" << endl;

	BinarySearchTree sFibTree(fib(n));
	sFibTree.print();

	for (int i = 0; i < 2; i++) cout << "Tree contains " << vals[i] << ": " << sFibTree.contains(vals[i]) << endl;

	cout << endl << "ASSIGNMENT 2:" << endl;
	cout << "Tree of size " << n << " has an internal path length of " << smallerTree.calculateInternalPathLength() << "." << endl << endl;

	cout << "---" << endl << "TREE TESTING: " << endl;

	Stopwatch sW;
	ConsoleMatrix cM(6, 3);

	//Clock Name
	string cN1, cN2, cN3;

	ConsoleMatrix cM2(3, 3);
	cM2.addRow(vector<string>({ "N:", to_string(N), "Number of elements." }));
	cM2.addRow(vector<string>({ "randN:", to_string(randN), "Number of random indexes for the random searches." }));

	// Assignment 1 Code
	cN1 = "NTreeCreation";
	sW.start(cN1);
	BinarySearchTree tree1(N);
	sW.stop(cN1);

	cN2 = "2NTreeCreation";
	sW.start(cN2);
	BinarySearchTree tree2(2 * N);
	sW.stop(cN2);

	cM.addRow(vector<string>({ "Operation:", "Tree (size N):", "Tree (size 2N):", "Comparison: ", "Tree (size N, " + to_string(threads) + " threads):", "Comparison:" }));

	cN3 = "MultiThreadedTreeCreation";
	sW.start(cN3);
	BinarySearchTree tree3(N, threads);
	sW.stop(cN3);
	cM.addRow(vector<string>({ "Tree Creation", sW.getString(cN1), sW.getString(cN2), to_string(sW.getTime(cN2) / sW.getTime(cN1)), sW.getString(cN3), to_string(sW.getTime(cN3) / sW.getTime(cN1)) }));

	cM.addRow("");
	cM.addRow(vector<string>({ "Operation:", "IndexTree:", "VectorTree:", "Comparison: " }));

	cN2 = "VectorTreeCreation";
	std::vector<int> fibs = fib(N);
	sW.start(cN2);
	BinarySearchTree lFibsTree(fibs);
	sW.stop(cN2);
	cM.addRow(vector<string>({ "Creation", sW.getString(cN1), sW.getString(cN2), to_string(sW.getTime(cN2) / sW.getTime(cN1)) }));

	cM.addRow("");
	cM.addRow(vector<string>({ "Operation:", "Tree:", "Vector:", "Comparison: " }));

	cN2 = "VectorCreation";
	sW.start(cN2);
	vector<int> comparisonVector(N);
	for (int i = 0; i < N; i++) comparisonVector[i] = i;
	sW.stop(cN2);
	cM.addRow(vector<string>({ "Creation", sW.getString(cN1), sW.getString(cN2), to_string(sW.getTime(cN2) / sW.getTime(cN1)) }));

	cN1 = "NTreeSearchHitWorstCase";
	sW.start(cN1);
	tree1.contains(0);
	sW.stop(cN1);

	bool result = false;
	cN2 = "VectorSearchHitWorstCase";
	sW.start(cN2);
	for (int i = 0; i < N; i++) {
		result |= (comparisonVector[i] == N - 1);
		if (result) break;
	}
	sW.stop(cN2);
	cM.addRow(vector<string>({ "Search Worst Case", sW.getString(cN1), sW.getString(cN2), to_string(sW.getTime(cN2) / sW.getTime(cN1)) }));

	cN1 = "NTreeSearchMissWorstCase";
	sW.start(cN1);
	tree1.contains(-1);
	sW.stop(cN1);

	result = false;
	cN2 = "VectorSearchMiss";
	sW.start(cN2);
	for (int i = 0; i < N; i++) {
		result |= (comparisonVector[i] == N);
		if (result) break;
	}
	sW.stop(cN2);
	cM.addRow(vector<string>({ "Search Miss", sW.getString(cN1), sW.getString(cN2), to_string(sW.getTime(cN2) / sW.getTime(cN1)) }));

	vector<int> randomElementValues(randN);
	for (int i = 0; i < randN; i++) randomElementValues[i] = ((double)rand() / (double)RAND_MAX) * (N - 1);

	cN1 = "NTreeSearchRandomHits";
	double time = 0;
	sW.start(cN1);
	for (int i = 0; i < randN; i++) tree1.contains(randomElementValues[i]);
	sW.stop(cN1);

	cN2 = "VectorSearchRandomHits";
	sW.start(cN2);
	for (int j = 0; j < randN; j++) {
		result = false;
		for (int i = 0; i < N; i++) {
			result |= (comparisonVector[i] == randomElementValues[j]);
			if (result) break;
		}
	}
	sW.stop(cN2);
	cM.addRow(vector<string>({ "Search Random", sW.getString(cN1), sW.getString(cN2), to_string(sW.getTime(cN2) / sW.getTime(cN1)) }));

	cM.addRow("");

	cM.addRow(vector<string>({ "Operation:", "Length:", "Time:" }));
	// Assignment 2 Code
	cN1 = "InternalLength";
	sW.start(cN1);
	int internalPathLength = tree1.calculateInternalPathLength();
	sW.stop(cN1);
	cM.addRow(vector<string>({ "Internal Path Length", to_string(internalPathLength), sW.getString(cN1) }));

	cM2.print();
	cout << endl;
	cM.print();
	cout << endl;

	string a;
	cin >> a;

    return 0;
}

std::vector<int> fib(size_t N) {
	std::vector<int> nums({0, 1});
	for (int i = 2; i < N; i++) nums.push_back(nums[i - 2] + nums[i - 1]);
	return nums;
}
