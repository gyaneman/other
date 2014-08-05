import java.util.Random;
import java.util.Scanner;

public class Shortest_path {
	
	public static void printAll(int numV, int[][] e){
		for(int i = 0; i < numV; i++){
			for(int j = 0; j < numV; j++){
				System.out.print(e[i][j] + " ");
			}
			System.out.println();
		}
	}
	
	public static void generateRandom(int numV, int numE, int[][] e){
		Random rand = new Random();
		int r1, r2, r3;
		
		for(int i = 0; i < numE; i++){
			r1 = rand.nextInt(numV);
			r2 = rand.nextInt(numV);
			while(r1 == r2 || e[r1][r2] != 0) {
				r1 = rand.nextInt(numV);
				r2 = rand.nextInt(numV);
			}	
			r3 = rand.nextInt(50) + 1;
			e[r1][r2] = r3;
			e[r2][r1] = r3;
		}
	}
	
	public static void input(int numV, int numE, int[][] e){
		Scanner scan = new Scanner(System.in);
		int a, b, w;
		for(int i = 0; i < numE; i++){
			a = scan.nextInt();
			b = scan.nextInt();
			w = scan.nextInt();
			e[a-1][b-1] = w;
			e[b-1][a-1] = w;
		}
	}
	
	public static void main(String[] args) {
		// TODO 自動生成されたメソッド・スタブ
		Scanner scan = new Scanner(System.in);
		int numV = scan.nextInt();
		//int numE = numV * 3;
		int numE = scan.nextInt();
		int start = scan.nextInt();
		
		/* 辺の重み */
		int[][] e = new int[numV][numV];
		/* 始点から各頂点の最短距離 */
		int[] D = new int[numV];
		/* Dの初期化 無限を-1とする */
		for(int i = 0; i < D.length; i++)
			D[i] = Integer.MAX_VALUE;
		
		/* 始点を0にする */
		D[start-1] = 0;
		
		/* 辺の集合 S */
		int[] S = new int[numV];
		
		//generateRandom(numV, numE, e);
		input(numV, numE, e);
		//System.out.println("ok");
		printAll(numV, e);
		
		/* Sの初期化 */
		for(int j = 0; j < S.length; j++)
			S[j] = 0;
			
		for(int i = 0; i < numV; i++){
			/* Dの最小値かつSに含まない頂点をみつける */
			int min = Integer.MAX_VALUE;
			int minv = 0;
			for(int j = 0; j < D.length; j++){
				if(min > D[j] && S[j] == 0){
					min = D[j];
					minv = j;
				}
			}
			
			S[minv] = 1;
			//System.out.println(minv);
			for(int j = 0; j < numV; j++){
				if(e[minv][j] != 0 && S[j] == 0){
					D[j] = Math.min(D[j], D[minv] + e[minv][j]);
				}
			}
		}
		
		for(int i = 0; i < D.length; i++){
			System.out.println(D[i] + "  " + S[i]);
		}
	}

}
