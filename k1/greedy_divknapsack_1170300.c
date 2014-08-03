#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count = 0;

typedef struct Element{
	int value;
	int weight;
	double vperw;
} Element;

int getRandom(int min, int max){
	srand((unsigned int)time(NULL));		//なぜかこれするとバグるんだが...
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void swap(Element *a, Element *b){
	Element tmp = *a;
	*a = *b;
	*b = tmp;
}

void quickSort(Element *eldata, int left, int right){
	int i = left;
	int j = right;
	Element pivot = eldata[(left + right) / 2];
	
	while(1){
		while(eldata[i].vperw > pivot.vperw) i++;
		while(pivot.vperw > eldata[j].vperw) j--;
		if(i >= j) break;
		swap(eldata+i, eldata+j);
		i++; j--;
	}
	if(left < i-1) quickSort(eldata, left, i-1);
	if(j+1 < right) quickSort(eldata, j+1, right);
	count++;
}

void printAll(Element *eldata, int n){
	int i;
	for(i = 0; i < n; i++){
		printf("%d...%d...%lf\n", 
			eldata[i].weight, eldata[i].value, eldata[i].vperw);
	}
}

int main(){
	Element *eldata;
	Element element;
	int i, n, c;
	double ans;
	double cd1, cd2;
	clock_t start, end;
	
	/* input n and c */
	printf("要素の数を入力してください: ");
	scanf("%d", &n);
	printf("ナップサックの容量を入力してください:");
	scanf("%d", &c);
	
	eldata = (Element*)calloc(n, sizeof(Element));
	
	/* Generate random numbers and print numbers*/
	for(i = 0; i < n; i++){
		eldata[i].weight = getRandom(1, n);
		eldata[i].value = getRandom(1, n) * 10;
		eldata[i].vperw = (double)eldata[i].value / (double)eldata[i].weight;
		//printf("%d    重さ...%d    価値...%d\n", 
		//		i+1, eldata[i].value, eldata[i].weight);
	}
	
	/* sort */
	quickSort(eldata, 0, n-1);
	
	/* debug */
	printAll(eldata, n);
	
	/* solve greedy divknapsack */
	start = clock();
	ans = 0;
	cd1 = (double)c;
	for(i = 0, element = eldata[0]; i < n; i++, element = eldata[i]){
		cd2 = cd1;
		cd1 -= element.weight;
		if(cd1 < 0.0){
			ans += (cd2 / element.weight) * element.value;
			break;
		}
		ans += element.value;
	}
	end = clock();
	
	printf("答え...%lf\n", ans);
	printf("count...%d\n", count);
	printf("excution time...%d[ms]\n", end-start);
	
	return 0;
}