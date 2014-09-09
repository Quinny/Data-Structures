public class Node<T extends Comparable<? super T>>{
	private T val;
	private Node right;
	private Node left;
	public Node(){
		right=null;
		left=null;
	}
	public Node(T v){
		val=v;
		right=null;
		left=null;
	}
	public Node right(){
		return right;
	}
	public Node left(){
		return left;
	}
	public T val(){
		return val;
	}
	public void setRight(Node r){
		right=r;
	}
	public void setLeft(Node l){
		left=l;
	}

	public String toString(){
		return val+"";
	}
}