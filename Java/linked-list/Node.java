public class Node<T>{
	private T val;
	private Node next;
	private Node prev;
	public Node(){
		val=null;
		next=null;
		prev=null;
	}
	public Node(T v){
		val=v;
	}
	public Node(T v,Node n,Node p){
		val=v;
		next=n;
		prev=p;
	}
	public T getVal(){
		return val;
	}
	public Node getNext(){
		return next;
	}
	public Node getPrev(){
		return prev;
	}
	public void setVal(T v){
		val=v;
	}
	public void setNext(Node n){
		next=n;
	}
	public void setPrev(Node p){
		prev=p;
	}
	public String toString(){
		return val+"";
	}
}