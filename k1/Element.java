
public class Element {
	int value;
	int weight;
	double vperw;
	
	public Element(int v, int w){
		this.value = v;
		this.weight = w;
		this.vperw = (double)v / (double)w;
	}
	
	public int getValue(){
		return this.value;
	}
	
	public int getWeight(){
		return this.weight;
	}
	
	public double getVperw(){
		return this.vperw;
	}
	
	public double getSplitValue(double w){
		return (w / this.weight) * this.value;
	}
}
