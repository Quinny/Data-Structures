public class Stack<T>{

	private Node head;

	public Stack(){
		head=null;
	}

	public void push(T v){
		if(head==null){
			head=new Node(v);
		}
		else{
			Node nw=new Node(v,head);
			head=nw;
		}
	}
	public void pop(){
		head=head.next();
	}

	public T peek(){
		return (T)head.val();
	}

	public boolean isEmpty(){
		return head==null;
	}
}