#include "Blyz.h"
#include <iostream>
#include <boost/chrono/chrono.hpp>
#include <fstream>
#include <string>

void setUpTesting(int, int, int**&, int**&);
void setUpTesting(int, int, int**&);
template <typename T>
void deallocate2DArr(T**, int);
void displayResults(std::string name, double**, int, int, int*, float*);
void allocateTimes(double**&, int, int);

int main()
{
	std::fstream output;

	bool debug = true;

	const int test_cases = 19;
	int test_case[test_cases] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
	const int edge = 5;
	float edges[edge] = { .2 , .4, .6, .8, 1.0};
	int average = 10;
	float** arr = nullptr;
	Blyz::Prim* prims = nullptr;
	Blyz::Kruskal* kruskals = nullptr;
	int** A = nullptr;
	int** height = nullptr;
	int** near = nullptr;
	double** prims_times = nullptr;
	double** kruskal_times = nullptr;

	if (debug)
		output.open("output_main.txt", std::ios::out);

	allocateTimes(prims_times, test_cases, edge);

	for (int i = 0; i < test_cases; i++)
	{
		for (int k = 0; k < edge; k++)
		{
			if (debug)
			{
				output << std::endl;
				output << "START-> n = " << test_case[i] << ", e = " << edges[k] << std::endl;
				output << std::endl;
			}
			Blyz::generateUndirectedGraph<float**>::generateAdjMatrix(arr, test_case[i], edges[k]);

			setUpTesting(average, test_case[i], near);
			prims = new Blyz::Prim((const float**)arr, test_case[i]);

			if (debug)
				prims->viewCostArr(output);

			auto t1 = boost::chrono::high_resolution_clock::now();
			for (int j = 0; j < average; j++)
			{
				if (j != 0)
					prims->cutDownTheTree();
				prims->findMinTree(near[j]);
			}
			auto t2 = boost::chrono::high_resolution_clock::now();

			auto time_span = boost::chrono::duration_cast<boost::chrono::duration<double, boost::nano>>(t2 - t1);
			prims_times[i][k] = ((double)(time_span.count()) / (double)(average));

			if (debug)
			{
				output << std::endl;
				prims->viewTreeArr(output);
				output << std::endl;
				output << "TOTAL MIN COST: " << prims->getMinCost() << std::endl;
				output << "TREE SIZE: " << prims->getTreeSize() << std::endl;
			}

			if (debug)
			{
				if (prims->getTreeSize() < test_case[i] - 1)
					output << "Not a min spanning tree" << std::endl;
			}

			deallocate2DArr(arr, test_case[i]);

			delete prims;
		}

		deallocate2DArr(near, average);
	}

	displayResults("Prim's", prims_times, test_cases, edge, test_case, edges);
	deallocate2DArr(prims_times, test_cases);
	arr = nullptr;
	allocateTimes(kruskal_times, test_cases, edge);

	output << "START KRUSTAL" << std::endl;

	for (int i = 0; i < test_cases; i++)
	{
		for (int k = 0; k < edge; k++)
		{
			if (debug)
			{
				output << std::endl;
				output << "START-> n = " << test_case[i] << ", e = " << edges[k] << std::endl;
				output << std::endl;
			}
			Blyz::generateUndirectedGraph<float**>::generateAdjMatrix(arr, test_case[i], edges[k]);

			setUpTesting(average, test_case[i], A, height);
			kruskals = new Blyz::Kruskal((const float**)arr, test_case[i]);

			if (debug)
				kruskals->viewCostArr(output);

			auto t1 = boost::chrono::high_resolution_clock::now();

			for (int j = 0; j < average; j++)
			{
				if (j != 0)
					kruskals->cutDownTheTree();
				kruskals->findMinTree(A[j], height[j]);
			}

			auto t2 = boost::chrono::high_resolution_clock::now();

			auto time_span = boost::chrono::duration_cast<boost::chrono::duration<double, boost::nano>>(t2 - t1);
			kruskal_times[i][k] = ((double)(time_span.count()) / (double)(average));

			if (debug)
			{
				output << std::endl;
				kruskals->viewTreeArr(output);
				output << std::endl;
				output << "TOTAL MIN COST: " << kruskals->getMinCost() << std::endl;
				output << "TREE SIZE: " << kruskals->getTreeSize() << std::endl;
			}

			if (debug)
			{
				if (kruskals->getTreeSize() < test_case[i] - 1)
					output << "Not a min spanning tree" << std::endl;
			}

			deallocate2DArr(arr, test_case[i]);

			delete kruskals;
		}

		deallocate2DArr(A, average);
		deallocate2DArr(height, average);
	}

	displayResults("kruskal's", kruskal_times, test_cases, edge, test_case, edges);
	deallocate2DArr(kruskal_times, test_cases);

	output << "END PROGRAM" << std::endl;
}

void setUpTesting(int avg, int size, int**& near)
{
	near = new int*[avg];

	for (int i = 0; i < avg; i++)
		near[i] = new int[size];

	for (int i = 0; i < avg; i++)
	{
		near[i][0] = -1;

		for (int j = 1; j < size; j++)
			near[i][j] = 0;
	}
}

void setUpTesting(int avg, int size, int**& A, int**& H)
{
	A = new int*[avg];

	for (int i = 0; i < avg; i++)
		A[i] = new int[size];

	for (int i = 0; i < avg; i++)
	{
		for (int j = 0; j < size; j++)
			A[i][j] = j;
	}

	H = new int*[avg];

	for (int i = 0; i < avg; i++)
		H[i] = new int[size];

	for (int i = 0; i < avg; i++)
	{
		for (int j = 0; j < size; j++)
			H[i][j] = -1;
	}


}

template <typename T>
void deallocate2DArr(T** arr, int size)
{
	if (arr != nullptr)
	{
		for (int i = 0; i < size; i++)
			delete[] arr[i];
		delete[] arr;
	}
}

void allocateTimes(double**& times, int n, int e)
{
	times = new double*[n];

	for (int i = 0; i < n; i++)
		times[i] = new double[e];
}

void displayResults(std::string name, double** arr, int n, int e, int* ns, float* es)
{
	std::fstream output2;

	output2.open(name + "_results.txt", std::ios::out);

	output2 << std::endl;
	output2 << "Results for: " << name <<  std::endl;
	output2 << std::endl;

	for (int i = 0; i < n; i++)
	{
		output2 << "n = " << ns[i] << std::endl;

		for (int j = 0; j < e; j++)
		{
			output2 << "e = " << es[j] << std::endl;
			output2 << std::fixed << std::setprecision(15);
			output2 << std::fixed << std::setprecision(15) << arr[i][j] << std::fixed << std::setprecision(15) << std::endl;
			output2 << std::endl;
		}
		output2 << std::endl;
	}

	output2.close();
}


