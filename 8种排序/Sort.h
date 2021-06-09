#pragma once
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
void PrintArray(int* a, int n);
void InsertSort(int* a, int n);//插入排序
void ShellSort(int* a, int n);//希尔排序
void BubbleSort(int* a, int n);//冒泡排序
void HeapSort(int* a, int n, int root);//堆排序
void SelectSort(int* a, int n);//选择排序
void QuickSort(int* a, int begin, int end);//快速排序
void QuickSortNonR(int* a, int left, int right);//快排非递归
void MergeSort(int* a, int n);//归并排序
void MergeSortNonR(int* a, int n);//归并非递归
void MergeSortFile(const char* file);//外排序 文件排序
void CountSort(int* a, int n);//计数排序