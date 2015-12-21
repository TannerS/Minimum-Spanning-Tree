#pragma once 

#include <iostream>
#include <cmath>
#include <iomanip>
#include <boost\io\ios_state.hpp>
#include "Blyz.h"
#include <fstream>

namespace Blyz
{
#pragma region Prim Functions

	Prim::Prim(const float** arr, int n) : treesizeC(2), cost(arr)
	{
		treennodes = 0;
		treesizeR = 0;
		mincost = 0;
		sizeN = n;
	}

	// so each loop can reset tree
	void Prim::cutDownTheTree()
	{
		if (tree != nullptr)
		{
			for (int i = 0; i < treesizeR; i++)
				delete[] tree[i];
			delete[] tree;

			treesizeR = 0;
		}

		tree = nullptr;
		treennodes = 0;
	}

	int** Prim::getTree()
	{
		return tree;
	}

	void Prim::findMinTree(int* near)
	{
		int j = 0;
		mincost = 0;
		treennodes = 0;

		for (int i = 0; i <= sizeN - 2; i++)
		{
			j = findMin(near);

			if (j != -1)
			{
				addToTree(j, near[j]);
				mincost += cost[j][near[j]];
				near[j] = -1;

				for (int k = 0; k <= sizeN - 1; k++)
				{
					if (near[k] != -1)
					{
						if (cost[k][near[k]] > cost[k][j])
							near[k] = j;
					}
				}
			}
		}
	}

	void Prim::addToTree(int x, int y)
	{
		expandTree();
		tree[treesizeR - 1][0] = x;
		tree[treesizeR - 1][1] = y;
		treennodes++;
	}

	int Prim::getTreeSize()
	{
		return treennodes;
	}

	void Prim::expandTree()
	{
		if (tree == nullptr)
		{
			treesizeR++;
			tree = new int*[treesizeR];

			for (int i = 0; i < treesizeR; i++)
				tree[i] = new int[treesizeC];
		}
		else
		{
			int temp_size = treesizeR + 1;
			int** temp = new int*[temp_size];

			for (int i = 0; i < temp_size; i++)
				temp[i] = new int[treesizeC];

			for (int i = 0; i < treesizeR; i++)
			{
				for (int j = 0; j < treesizeC; j++)
					temp[i][j] = tree[i][j];
			}

			for (int i = 0; i < treesizeR; i++)
				delete[] tree[i];
			delete[] tree;

			tree = temp;
			treesizeR++;
		}
	}

	int Prim::findMin(int* near)
	{
		int j = -1;
		float min = std::numeric_limits<int>::max();

		for (int i = 0; i < sizeN; i++)
		{
			if (near[i] != -1)
			{
				if (cost[i][near[i]] != std::numeric_limits<float>::infinity())
				{
					if (cost[i][near[i]] < min)
					{
						min = cost[i][near[i]];
						j = i;
					}
				}
			}
		}
		return j;
	}

	float Prim::getMinCost()
	{
		return mincost;
	}

	void Prim::viewCostArr(std::fstream& output)
	{
		if (sizeN <= 10)
		{
			output << std::setw(5);
			for (int i = 0; i < sizeN; i++)
				output << std::setw(5) << i;
			output << " " << std::endl;
			boost::io::ios_all_saver guard(output);

			for (int i = 0; i < sizeN * 5; i++)
				output << "-";
			output << " " << std::endl;
			guard.restore();

			for (int i = 0; i < sizeN; i++)
			{
				output << i << "| ";
				boost::io::ios_all_saver guard2(output);
				std::cout.setf(std::ios_base::left);

				for (int j = 0; j < sizeN; j++)
				{
					output << std::setw(5) << std::left;
					output << cost[i][j];
				}
				output << std::endl;
			}
			output.unsetf(std::ios_base::left);
		}
	}

	void Prim::viewTreeArr(std::fstream& output)
	{
		if (sizeN <= 10)
		{
			output << "TREE" << std::endl;
			for (int i = 0; i < this->treesizeR; i++)
			{
				for (int j = 0; j < this->treesizeC; j++)
					output << this->tree[i][j] << " ";
				output << std::endl;
			}
			output << "TREE END" << std::endl;
		}
	}

#pragma endregion

#pragma region Kruskal Functions

	Kruskal::Kruskal(const float** arr, int size) : treesizeC(2), cost(arr)
	{
		sizeN = size;
		treesizeR = 0;
		treennodes = 0;
		mincost = 0;
		sizeE = 0;

		for (int i = 0; i < sizeN; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (arr[i][j] != std::numeric_limits<float>::infinity())
					sizeE++;
			}
		}
	}

	void Kruskal::cutDownTheTree()
	{
		if (tree != nullptr)
		{
			for (int i = 0; i < treesizeR; i++)
				delete[] tree[i];
			delete[] tree;

			treesizeR = 0;
		}

		tree = nullptr;
		treennodes = 0;
	}

	void Kruskal::merge3(int* height, int* A, int a, int b)
	{
		if (height[a] == height[b])
		{
			A[b] = a;
			height[a] = height[a] + 1;
		}
		else
		{
			if (height[a] > height[b])
				A[b] = a;
			else
				A[a] = b;
		}
	}

	int Kruskal::find2(int* A, int x)
	{
		int i = x;
		while (A[i] != i)
			i = A[i];
		return i;
	}

	void Kruskal::findMinTree(int* A, int* H)
	{
		buildHeap();

		mincost = 0;
		treennodes = 0;
		int i = 0;
		int u = 0, v = 0, k = 0, j = 0;

		heap_size = sizeE;

		while ((i <= sizeN - 1) && (!(heap_size <= 0)))
		{
			u = edges[heap_size - 1].x;
			v = edges[heap_size - 1].y;

			deleteRoot();

			j = find2(A, u);
			k = find2(A, v);

			if (j != k)
			{
				i++;
				addToTree(u, v);
				mincost = mincost + cost[u][v];
				merge3(H, A, j, k);
			}
		}
	}

	float Kruskal::getMinCost()
	{
		return mincost;
	}

	int Kruskal::getTreeSize()
	{
		return treennodes;
	}

	void Kruskal::buildHeap()
	{
		edges = new Edges[sizeE];

		int k = 0;

		for (int i = 0; i < sizeN; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (cost[i][j] != std::numeric_limits<float>::infinity())
				{
					edges[k].cost = cost[i][j];
					edges[k].x = i;
					edges[k].y = j;
					k++;
					heap_size++;
				}
			}
		}

		Blyz::EdgeHeap::maxHeapSort(edges, sizeE);
	}

	void Kruskal::expandTree()
	{
		if (tree == nullptr)
		{
			treesizeR++;
			tree = new int*[treesizeR];

			for (int i = 0; i < treesizeR; i++)
				tree[i] = new int[treesizeC];
		}
		else
		{
			int temp_size = treesizeR + 1;
			int** temp = new int*[temp_size];

			for (int i = 0; i < temp_size; i++)
				temp[i] = new int[treesizeC];

			for (int i = 0; i < treesizeR; i++)
			{
				for (int j = 0; j < treesizeC; j++)
					temp[i][j] = tree[i][j];
			}

			for (int i = 0; i < treesizeR; i++)
				delete[] tree[i];
			delete[] tree;

			tree = temp;
			treesizeR++;
		}
	}

	void Kruskal::addToTree(int x, int y)
	{
		expandTree();
		tree[treesizeR - 1][0] = x;
		tree[treesizeR - 1][1] = y;
		treennodes++;
	}

	void Kruskal::viewTreeArr(std::fstream& output)
	{
		if (sizeN <= 10)
		{
			output << "TREE" << std::endl;
			for (int i = 0; i < this->treesizeR; i++)
			{
				for (int j = 0; j < this->treesizeC; j++)
					output << this->tree[i][j] << " ";
				output << std::endl;
			}
			output << "TREE END" << std::endl;
		}
	}

	void Kruskal::deleteRoot()
	{
		if (edges != nullptr)
		{
			if (heap_size == 1)
			{
				delete[] edges;
				heap_size--;
			}
			else
				heap_size--;
		}
	}

	void Kruskal::viewCostArr(std::fstream& output)
	{
		if (sizeN <= 10)
		{
			output << std::setw(5);
			for (int i = 0; i < sizeN; i++)
				output << std::setw(5) << i;
			output << " " << std::endl;
			boost::io::ios_all_saver guard(output);

			for (int i = 0; i < sizeN * 5; i++)
				output << "-";
			output << " " << std::endl;
			guard.restore();

			for (int i = 0; i < sizeN; i++)
			{
				output << i << "| ";
				boost::io::ios_all_saver guard2(output);
				std::cout.setf(std::ios_base::left);

				for (int j = 0; j < sizeN; j++)
				{
					output << std::setw(5) << std::left;
					output << cost[i][j];
				}
				output << std::endl;
			}
			output.unsetf(std::ios_base::left);
		}
	}

#pragma endregion 

#pragma region EdgeHeapSort

	void EdgeHeap::swap(Edges* arr, int elem1, int elem2)
	{

		Edges temp;

		temp.x = arr[elem1].x;
		temp.y = arr[elem1].y;
		temp.cost = arr[elem1].cost;

		arr[elem1].x = arr[elem2].x;
		arr[elem1].y = arr[elem2].y;
		arr[elem1].cost = arr[elem2].cost;

		arr[elem2].cost = temp.cost;
		arr[elem2].x = temp.x;
		arr[elem2].y = temp.y;
	}

	void EdgeHeap::maxHeapSort(Edges* arr, int size)
	{
		for (int cursor = ((int)floor((size / 2) - 1)); cursor >= 0; cursor--)
			maxHeapify(arr, cursor, size - 1);

		for (int cursor = size - 1; cursor >= 1; cursor--)
		{
			swap(arr, cursor, 0);
			maxHeapify(arr, 0, cursor - 1);
		}
	}

	void EdgeHeap::maxHeapify(Edges* arr, int parent, int size)
	{
		int lchild = (parent * 2) + 1;
		int rchild = (parent * 2) + 2;
		int smallest = 0;

		if (lchild <= size && arr[lchild].cost < arr[parent].cost)
			smallest = lchild;
		else
			smallest = parent;

		if (rchild <= size && arr[rchild].cost < arr[smallest].cost)
			smallest = rchild;

		if (smallest != parent)
		{
			swap(arr, smallest, parent);
			maxHeapify(arr, smallest, size);
		}
	}

#pragma endregion 

}


