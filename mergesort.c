/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

int min(int a, int b) {
	return (a < b) ? a : b;
}

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
	int i, j, k;
	i = leftstart; /* index for the left subarray */
	j = rightstart; /* index for the right subarray */
	k = leftstart; /* index for the temp array */

	/* merge the two subarrays into the temp array */
	while (i <= leftend && j <= rightend){
		if (A[i] <= A[j]){
			B[k++] = A[i++];
		} else {
			B[k++] = A[j++];
		}
	}

	/* copy the remaining elements of the left subarray, if any */
	while (i <= leftend){
		B[k++] = A[i++];
	}

	/* copy the remaining elements of the right subarray, if any */
	while (j <= rightend){
		B[k++] = A[j++];
	}

	/* copy back the merged elements to the original array */
	memcpy(&A[leftstart], &B[leftstart], (rightend - leftstart + 1) * sizeof(int));

	return;
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
	if (left < right){
		int mid = (left + right) / 2;
		my_mergesort(left, mid);
		my_mergesort(mid + 1, right);
		merge(left, mid, mid + 1, right);
	}
	return;
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
	pthread_t left_thread, right_thread;
	struct argument *args = (struct argument *)arg;
	
	/* base case: if we have reached the cutoff level, we just call my_mergesort() */
	if (args->level >= min(cutoff, 5) || args->left >= args->right){
		my_mergesort(args->left, args->right);
		return NULL;
	}

	/* recursive case: we create two threads to sort the two halves */
	int mid = (args->left + args->right) / 2;
	struct argument * left_args = buildArgs(args->left, mid, args->level + 1);
	struct argument * right_args = buildArgs(mid + 1, args->right, args->level + 1);
	
	pthread_create(&left_thread, NULL, parallel_mergesort, (void *) left_args);
	pthread_create(&right_thread, NULL, parallel_mergesort, (void *) right_args);
	
	/* wait for the two threads to finish */
	pthread_join(left_thread, NULL);
	pthread_join(right_thread, NULL);
	
	/* merge the two sorted halves */
	merge(args->left, mid, mid + 1, args->right);

	/* free the allocated memory for arguments */
	free(left_args);
	free(right_args);
	return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
	struct argument *args = (struct argument *) malloc(sizeof(struct argument));
	args->left = left;
	args->right = right;
	args->level = level;
	return args;
}

