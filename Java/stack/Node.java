public class Node<T>{
	private Node next;
	private T val;
	public Node(){
		next=null;
		val=null;
	}
	public Node(T v){
		next=null;
		val=v;
	}
	public Node(T v,Node n){
		next=n;
		val=v;
	}
	public T val(){
		return val;
	}
	public Node next(){
		return next;
	}
	public void setVal(T v){
		val=v;
	}
	public void setNext(Node n){
		next=n;
	}
}