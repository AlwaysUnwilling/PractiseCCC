#pragma once
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
void PrintArray(int* a, int n);
void InsertSort(int* a, int n);//��������
void ShellSort(int* a, int n);//ϣ������
void BubbleSort(int* a, int n);//ð������
void HeapSort(int* a, int n, int root);//������
void SelectSort(int* a, int n);//ѡ������
void QuickSort(int* a, int begin, int end);//��������
void QuickSortNonR(int* a, int left, int right);//���ŷǵݹ�
void MergeSort(int* a, int n);//�鲢����
void MergeSortNonR(int* a, int n);//�鲢�ǵݹ�
void MergeSortFile(const char* file);//������ �ļ�����
void CountSort(int* a, int n);//��������