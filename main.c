#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void *Alloc(size_t sz)
{
	extraMemoryAllocated += sz;
	size_t* ret = malloc(sizeof(size_t) + sz);
	*ret = sz;
	printf("Extra memory allocated, size: %ld\n", sz);
	return &ret[1];
}

void DeAlloc(void* ptr)
{
	size_t* pSz = (size_t*)ptr - 1;
	extraMemoryAllocated -= *pSz;
	printf("Extra memory deallocated, size: %ld\n", *pSz);
	free((size_t*)ptr - 1);
}

size_t Size(void* ptr)
{
	return ((size_t*)ptr)[-1];
}

void swapeth(int *ip, int *fp)
{
	int temp = *ip;
	*ip = *fp;
	*fp = temp;
}
void heapify(int arr[], int root_node, int n)
{
	int largest_node = root_node;
	int left_node = 2 * root_node + 1;
	int right_node = 2 * root_node + 2;
	if(left_node < n && arr[left_node] > arr[largest_node])
		largest_node = left_node;
	if(right_node < n && arr[right_node] > arr[largest_node])
		largest_node = right_node;
	if(largest_node != root_node)
	{
		swapeth(&arr[root_node], &arr[largest_node]);
		heapify(arr, n , largest_node);
	}
}
// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
	for(int i = n/2 - 1; i >= 0; i--)
	{
		heapify(arr, n, i);
	}
	for(int i = n -1; i >= 0; i--)
	{
		swapeth(&arr[0], &arr[i]);
		heapify(arr, i, 0);
	}
}
void merge(int pData[], int l, int m, int r)
{
	int i, j, k;
	int nL = m - l + 1;
	int nR = r - m;
	// int tmpL[nL];
	// int tmpR[nR];
	int *tmpL = (int *)Alloc(sizeof(int) * nL);
	int *tmpR = (int *)Alloc(sizeof(int) * nR);
	for(i = 0; i < nL; i++)
	{
		tmpL[i] = pData[l + 1];
	}
	for(j = 0; j < nR; j++)
	{
		tmpR[j] = pData[m + 1 + j];
	}
	i = 0;
	j = 0;
	k = l;
	while(i < nL && j < nR)
	{
		if(tmpL[i] <= tmpR[j])
		{
			pData[k] = tmpL[i];
			i++;
		}
		else
		{
			pData[k] = tmpR[j];
			j++;
		}
		k++;
	}
	while(i < nL)
	{
		pData[k] = tmpL[i];
		i++;
		k++;
	}
	while(j < nR)
	{
		pData[k] = tmpR[j];
		j++;
		k++;
	}
	DeAlloc(tmpL);
	DeAlloc(tmpR);
}
// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if(l < r)
	{
		int m = l + (r - l) / 2;
		// int m = (l+r) / 2;
		mergeSort(pData, l , m);
		mergeSort(pData, m + 1, r);
		merge(pData, l, m, r);
	}
}
// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, j, i_dx;
	for(i = 1; i < n; i++)
	{
		i_dx = pData[i];
		j = i - 1;
		while(j >= 0 && pData[j] > i_dx)
		{
			pData[j + 1] = pData[j];
			j = j - 1;
		}
		pData[j + 1] = i_dx;
	}
	
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	int i, j;
	for(i = 0; i < n -1; i++)
	{
		for(j =0; j < n - i -1; j++)
		{
			if(pData[j+ 1] < pData[j])
			{
				swapeth(&pData[j], &pData[j + 1]);
			}									
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int i, j, min_Idx;
	for(i =0; i< n-1; i++)
	{
		min_Idx =i;
		for(j = i +1; j< n; j++)
		{
			if(pData[j] < pData[min_Idx])
				min_Idx = j;
		}
		if(min_Idx != i)
		{
			swapeth(&pData[min_Idx], &pData[i]);
		}
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)Alloc(sizeof(int) * dataSz);
		// Implement parse data block
		if(*ppData == NULL)
		{
			fclose(inFile);
			return -1;
		}
		for(i =0; i < dataSz; i++)
		{
			fscanf(inFile, "%d", &n);
			data = *ppData + i;
			*data = n;
		}
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
// void printArray(int pData[], int dataSz)
// {
// 	int i, sz = dataSz - 100;
// 	printf("\tData:\n\t");
// 	for (i=0;i<100;++i)
// 	{
// 		printf("%d ",pData[i]);
// 	}
// 	printf("\n\t");
	
// 	for (i=sz;i<dataSz;++i)
// 	{
// 		printf("%d ",pData[i]);
// 	}
// 	printf("\n\n");
// }

void printArray(int pData[], int dataSz)
{
    int i, sz = (dataSz > 100 ? dataSz - 100 : 0);
    int firstHundred = (dataSz < 100 ? dataSz : 100);
    printf("\tData:\n\t");
    for (i=0;i<firstHundred;++i)
    {
        printf("%d ",pData[i]);
    }
    printf("\n\t");
    
    for (i=sz;i<dataSz;++i)
    {
        printf("%d ",pData[i]);
    }
    printf("\n\n");
}


int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	// char* fileNames[1] = {"input1.txt"};
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	// for (i=0;i<1;++i)
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)Alloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

                printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		DeAlloc(pDataCopy);
		DeAlloc(pDataSrc);
	}
	
}
