#include <stdio.h>
#include "graph.h"

int main(){
	Graph *graph = make_Graph();
	int i;
	int numOfNode, numOfEge;
	int a, b, weight;
	int *result;
	int start;
	
	/* 頂点の数と辺の数の入力 */
	printf("頂点の数を入力してください: ");
	scanf("%d", &numOfNode);
	printf("辺の数を入力してください: ");
	scanf("%d", &numOfEge);
	
	/* ノードをつくる */
	for(i = 0; i < numOfNode; i++) addNode_Graph(graph);
	
	/* 辺をつくる */
	printf("ノード1の番号とノード2の番号, 重みを入力してください.\n");
	printf("例: 1番のノードと2番のノードをつないで5の重みをつけたいとき,\n");
	printf("1 2 5 と入力する\n");
	for(i = 0; i < numOfEge; i++){
		printf("%d:", i+1);
		scanf("%d %d %d", &a, &b, &weight);
		link_Graph(graph, a, b, weight);
	}
	
	/* スタートのノードを決定する */
	printf("始点を入力してください: ");
	scanf("%d", &start);
	
	/* ダイクストラで解く */
	result = (int*)malloc(sizeof(int) * numOfNode);
	solve_Dijkstra(graph, start, result);
	
	/* 結果を表示 */
	for(i = 0; i < numOfNode; i++)
		printf("%d...%d\n", i+1, result[i]);
	
	return 0;
}