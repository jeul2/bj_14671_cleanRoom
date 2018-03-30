/*
Q. Queue�� �ִ��ʿ������ �����س���
-�� ����: BFS�� 1���� ������, �����鼭 �� ���� ��, ��, ��, �� �� ������. 
Ǫ�� +1 -> �� -1 -> Ǫ�� +4 ....
�̷������� ��1���� �ϸ鼭 �ִ� 4���� �� �� �ִ�.
Ȱ������ �� �迭�� 1000 x 1000�̹Ƿ�
������������� ������ �����ϴܱ��� ������, Ǫ���� �뷫 2000�� �̷������
2000 * 4 = 8000ũ���� ť�������� ����������� �ȳ���.

Q. BFS�� �������.
-�� �������: �ѹ�Ž���ǰ��� �� ���� ������ �̷��, �ִ� ��Ʋ������ �������� �����صд�.
�����̰� �� �ڶ����� : ������ ������ �Ȱ��� ��
�����̰� �� ��á����1(�밢�����θ������� �Ϸ��Ϸ� ��ȭ�� ������) : ������ ������ �Ȱ��� ��
�����̰� �� ��á����2(�� ��á�µ� �Ϸ��Ϸ� ��ȭ�� ������ : �������� ������ �Ȱ�����

���� �������� �����߰�, �̸� Code��� ���������� �Ǻ��ؼ� �����ϴ� ����� �������.

*/

#include <stdio.h>

enum
{
	E_QUEUESIZE = 90000
};

struct S_POSITION
{
	int nRow;
	int nCol;
};

S_POSITION arQueue[E_QUEUESIZE]{};
int nQueueHead(0);
int nQueueTail(-1);
int nQueueSize(0);

void enqueue(int nRow, int nCol);
void dequeue(int *pRow, int *pCol);

void compareStateAtoB(int **ppSrc1, int **ppSrc2, int **ppSrc3, int nRowSize, int nColSize, int *pResCode);
void copyAndClearNewData(int **ppSrc1, int **ppSrc2, int **ppSrc3, int nRowSize, int nColSize);

void printData(int **ppSrc1, int nRowSize, int nColSize);

int main()
{
	int nInputRow(0); int nInputCol(0); int nInputMoldNum(0);
	int **ppData(nullptr);

	int nRow(0); int nCol(0);
	int nStateCode(0);
	int nMoldCount(0);
	int nNewMoldCount(0);
	int nFlagRow[4] = { 1, 1, -1, -1 };
	int nFlagCol[4] = { 1, -1, 1, -1 };
	int nSpreadRow(0); int nSpreadCol(0);

	int **ppNewData(nullptr);
	int **ppPreData(nullptr);

	//
	//freopen("input.txt", "r", stdin);

	scanf("%d %d %d", &nInputRow, &nInputCol, &nInputMoldNum);
	ppData = new int*[nInputRow] {};
	ppNewData = new int*[nInputRow] {};
	ppPreData = new int*[nInputRow] {};
	for (int i = 0; i < nInputRow; ++i)
	{
		ppData[i] = new int[nInputCol] {};
		ppNewData[i] = new int[nInputCol] {};
		ppPreData[i] = new int[nInputCol] {};
	}

	for (int i = 0; i < nInputMoldNum; ++i)
	{
		scanf("%d %d", &nRow, &nCol);
		--nRow;
		--nCol;
		enqueue(nRow, nCol);
		++nNewMoldCount;
	}

	while (nStateCode == 0)
	{
		nMoldCount = nNewMoldCount;
		nNewMoldCount = 0;

		while (nMoldCount != 0)
		{
			dequeue(&nRow, &nCol);
			for (int i = 0; i < 4; ++i)
			{
				nSpreadRow = nRow + nFlagRow[i];
				nSpreadCol = nCol + nFlagCol[i];
				if (nSpreadRow >= 0 && nSpreadRow < nInputRow && nSpreadCol >= 0 && nSpreadCol < nInputCol)
				{
					if (ppNewData[nSpreadRow][nSpreadCol] == 0)
					{
						ppNewData[nSpreadRow][nSpreadCol] = 1;
						enqueue(nSpreadRow, nSpreadCol);
						++nNewMoldCount;
					}
				}
			}
			--nMoldCount;
		}
		compareStateAtoB(ppNewData, ppData, ppPreData, nInputRow, nInputCol, &nStateCode);
		//
		//printf("<����>\n");
		//printData(ppNewData, nInputRow, nInputCol);
		//printf("<����>\n");
		//printData(ppData, nInputRow, nInputCol);
		//printf("<������>\n");
		//printData(ppPreData, nInputRow, nInputCol);
		//printf("<�����ڵ� : %d>\n", nStateCode);

		//
		copyAndClearNewData(ppNewData, ppData, ppPreData, nInputRow, nInputCol);
	}


	if (nStateCode == 1)
	{
		printf("YES\n");
	}
	else if (nStateCode == 2)
	{
		printf("NO\n");
	}


	for (int i = 0; i < nInputRow; ++i)
	{
		delete[] ppData[i];
		ppData[i] = nullptr;
		delete[] ppNewData[i];
		ppNewData = nullptr;
		delete[] ppPreData[i];
		ppPreData = nullptr;
	}
	delete[] ppData;
	ppData = nullptr;
	delete[] ppNewData;
	ppNewData = nullptr;
	delete[] ppPreData;
	ppPreData = nullptr;

	return 0;
}

void enqueue(int nRow, int nCol)
{
	if (nQueueSize > E_QUEUESIZE)
	{
		printf("overflow\n");
		return;
	}

	if (nQueueTail == E_QUEUESIZE - 1)
		nQueueTail = -1;
	++nQueueTail;
	arQueue[nQueueTail].nRow = nRow;
	arQueue[nQueueTail].nCol = nCol;
	++nQueueSize;
}

void dequeue(int * pRow, int * pCol)
{
	if (nQueueSize <= 0)
	{
		printf("underflow\n");
		return;
	}

	*pRow = arQueue[nQueueHead].nRow;
	*pCol = arQueue[nQueueHead].nCol;
	arQueue[nQueueHead].nRow = 0;
	arQueue[nQueueHead].nCol = 0;
	++nQueueHead;
	--nQueueSize;
	if (nQueueHead == E_QUEUESIZE)
		nQueueHead = 0;
}

void compareStateAtoB(int ** ppSrc1, int ** ppSrc2, int ** ppSrc3, int nRowSize, int nColSize, int * pResCode)
{
	int nSrc1ToSrc2(0);
	int nSrc1ToSrc3(0);
	int nFullNumber(0);
	int nCount(0);
	nFullNumber = nRowSize * nColSize;

	for (int i = 0; i < nRowSize; ++i)
	{
		for (int j = 0; j < nColSize; ++j)
		{
			if (ppSrc1[i][j] != ppSrc2[i][j])
			{
				nSrc1ToSrc2 = 1;
			}
			if (ppSrc1[i][j] != ppSrc3[i][j])
			{
				nSrc1ToSrc3 = 1;
			}
			if (ppSrc1[i][j] == 1)
			{
				++nCount;
			}

		}

	}

	if (nFullNumber == nCount)
	{
		*pResCode = 1;
	}
	else if (nSrc1ToSrc2 == 0 || nSrc1ToSrc3 == 0)
	{
		*pResCode = 2;
	}
	else
	{
		*pResCode = 0;
	}
}

void copyAndClearNewData(int ** ppSrc1, int ** ppSrc2, int ** ppSrc3, int nRowSize, int nColSize)
{
	for (int i = 0; i < nRowSize; ++i)
	{
		for (int j = 0; j < nColSize; ++j)
		{
			ppSrc3[i][j] = ppSrc2[i][j];
			ppSrc2[i][j] = ppSrc1[i][j];
			ppSrc1[i][j] = 0;
		}
	}

}

void printData(int ** ppSrc1, int nRowSize, int nColSize)
{
	for (int i = 0; i < nRowSize; ++i)
	{
		for (int j = 0; j < nColSize; ++j)
		{
			printf("[%d]", ppSrc1[i][j]);
		}
		printf("\n");
	}
	printf("------------\n");
}
