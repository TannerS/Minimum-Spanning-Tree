
#pragma once

#include <ctime>
#include <cstdlib>
#include <limits>  
#include <iostream>
#include <cmath>
#include <iomanip>
#include <boost\io\ios_state.hpp>

namespace Blyz
{
#pragma region Edge Struct

	struct Edges
	{
		float cost;
		int x;
		int y;
	};

#pragma endregion

#pragma region GenerateUnDirectedGraph

#pragma region GenerateUnDirectedGraph Class

	template <class T>
	class generateUndirectedGraph
	{
	private:
		static void fillAdjMatrix(T&);
		static void deleteEdges(T&);
		static int sizeN;
		static float edgeN;
		static void blankArr(T);

	public:
		static void generateAdjMatrix(T&, int, float);

	};

#pragma endregion 

#pragma region generateUndirectedGraph Static Variables Initializations

	template <typename T>
	int generateUndirectedGraph<T>::sizeN = 0;
	template <typename T>
	float generateUndirectedGraph<T>::edgeN = 0;

#pragma endregion 

#pragma region GenerateUnDirectedGraph Functions

	template <typename T>
	void generateUndirectedGraph<T>::generateAdjMatrix(T& arr, int size, float edges)
	{
		sizeN = size;
		edgeN = edges;

		arr = new float*[sizeN];
		for (int i = 0; i < sizeN; i++)
			arr[i] = new float[sizeN];

		deleteEdges(arr);
		fillAdjMatrix(arr);
	}

	template <typename T>
	void generateUndirectedGraph<T>::fillAdjMatrix(T& arr)
	{
		int ran = 0;
		for (int i = 0; i < sizeN; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				if (j != i)
				{
					if (arr[i][j] != std::numeric_limits<float>::infinity())
					{
						ran = (int)(rand() % 100 + 1);
						arr[i][j] = ran;
						arr[j][i] = ran;
					}
				}
				else
					arr[i][j] = 0;
			}
		}
	}

	template <typename T>
	void generateUndirectedGraph<T>::deleteEdges(T& arr)
	{
		srand(time(nullptr));
		int row = 0;
		int col = 0;

		int edge_max = 0;
		int edge_INF = 0;

		int possible_edges = 0;

		edge_max = sizeN - 1;
		edge_max = edge_max * sizeN;
		edge_max = edge_max / 2;

		possible_edges = edge_max * edgeN;
		possible_edges = (int)possible_edges;

		edge_INF = edge_max - possible_edges;

		blankArr(arr);

		int temp = sizeN - edgeN;

		int count = 0;

		while (count < edge_INF)
		{
			row = rand() % sizeN;
			col = rand() % sizeN;

			if (!(row == col || arr[row][col] == std::numeric_limits<float>::infinity()))
			{
				arr[row][col] = std::numeric_limits<float>::infinity();
				arr[col][row] = std::numeric_limits<float>::infinity();
				count++;
			}

		}
	}

	template <typename T>
	void generateUndirectedGraph<T>::blankArr(T arr)
	{
		for (int i = 0; i < sizeN; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				arr[i][j] = 0;
				arr[j][i] = 0;
			}
		}
	}

#pragma endregion

#pragma endregion

#pragma region Prim

#pragma region Prim Class

	class Prim
	{
	public:
		Prim(const float**, int);
		int** getTree();
		void findMinTree(int*);
		float getMinCost();
		int getTreeSize();
		void cutDownTheTree();
		// debugging purposes
		void viewTreeArr(std::fstream&);
		void viewCostArr(std::fstream&);

	private:
		int sizeN;
		const float** cost;
		int** tree;
		int treesizeR;
		float mincost;
		const int treesizeC;
		int findMin(int*);
		void addToTree(int, int);
		void expandTree();
		int treennodes;
	};

#pragma endregion 

#pragma endregion 

#pragma region Kruskal

	class Kruskal
	{
	private:
		void merge3(int*, int*, int, int);
		const float** cost;
		int sizeN;
		int sizeE;
		int size_temp;
		Blyz::Edges* edges;
		int** tree;
		int find2(int* A, int x);
		void buildHeap();
		int treesizeR;
		const int treesizeC;
		void expandTree();
		void addToTree(int, int);
		int treennodes;
		float mincost;
		void deleteRoot();

	public:
		void findMinTree(int* A, int* H);
		Kruskal(const float**, int);
		int getTreeSize();
		float getMinCost();
		int heap_size;
		void cutDownTheTree();
		// debugging purposes
		void viewTreeArr(std::fstream&);
		void viewCostArr(std::fstream&);
	};

#pragma endregion

#pragma endregion

#pragma region EdgeHeapSort

	class EdgeHeap
	{
	public:
		static void maxHeapSort(Edges*, int);

	private:
		static void swap(Edges*, int, int);
		static void maxHeapify(Edges*, int, int);
	};

#pragma endregion 
}
