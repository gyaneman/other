import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Random;
import java.util.Scanner;


public class greedy_divknapsack_1170300 {
	
	public static void printAll(ArrayList<Element> ary){
		for(Element el : ary){
			System.out.println(el.getValue() + "..." + el.getWeight() + "..." + el.getVperw());
		}
	}

	public static void main(String[] args) {
		// TODO 自動生成されたメソッド・スタブ
		Scanner scan = new Scanner(System.in);
		Random rnd = new Random();
		
		// 入力
		int n, c;
		System.out.print("要素の数を入力してください:");
		n = scan.nextInt();
		System.out.print("ナップサックの容量を入力してください:");
		c = scan.nextInt();
		
		// 乱数生成
		ArrayList<Element> ary = new ArrayList<Element>();
		for(int i = 0; i < n; i++){
			int v = rnd.nextInt(n) + 1;
			int w = (rnd.nextInt(n) + 1) * 100;
			Element element = new Element(v, w);
			ary.add(element);
			System.out.println((i+1) + "   価値..." + v + "   重さ..." + w);
		}
		
		// ソート
		Collections.sort(ary, new Comparator<Element>(){
			@Override
			public int compare(Element o1, Element o2) {
				// TODO 自動生成されたメソッド・スタブ
				if(o1.getVperw() < o2.getVperw()) return 1;
				if(o1.getVperw() > o2.getVperw()) return -1;
				return 0;
			}
		});
		
		// debug
		printAll(ary);
		
		// solve
		double ans = 0;
		double cdl = (double)c;
		for(Element el: ary){
			double cdl2 = cdl;
			cdl -= el.getWeight();
			if(cdl < 0.0) {
				ans += el.getSplitValue(cdl2);
				System.out.println(ans);
				break;
			}
			ans += el.getValue();
			System.out.println(ans);
		}
		System.out.println("答え..." + (int)ans);
	}

}
