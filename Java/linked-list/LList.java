public class LList<T>{
	private Node head;
	private Node tail;
	
	public LList(){
		head=null;
		tail=null;
	}

	public void add(T n){
		if(head==null){
			head=new Node(n);
			tail=head;
		}
		else{
			Node node=new Node(n);
			tail.setNext(node);
			node.setPrev(tail);
			tail=node;
		}
	}

	public void push(T n){
		Node node=new Node(n,head,null);
		head.setPrev(node);
		head=node;

	}

	public void remove(T n){
		Node tmp=head;
		while(tmp.getVal()!=n && tmp!=null) tmp=tmp.getNext();

		if(tmp==null)return;

		if(tmp==head){
			head=head.getNext();
			head.setPrev(null);
		}
		else if(tmp==tail){
			tail=tail.getPrev();
			tail.setNext(null);
		}
		else{
			tmp.getPrev().setNext(tmp.getNext());
			tmp.getNext().setPrev(tmp.getPrev());
		}
	}

	public void pop(){
		head=head.getNext();
		head.setPrev(null);
	}

	public int size(){
		int s=0;
		Node tmp=head;
		while(tmp!=null){
			s++;
			tmp=tmp.getNext();
		}
		return s;
	}

	public T peek(){
		return (T)head.getVal();
	}

	public T get(int i){
		int j=0;
		Node tmp=head;
		while(tmp!=null && j!=i){
			tmp=tmp.getNext();
			j++;
		}
		if(tmp==null) return null;

		return (T)tmp.getVal();
	}

	public void set(int i,T v){
		int j=0;
		Node tmp=head;
		while(tmp!=null && j!=i){
			tmp=tmp.getNext();
			j++;
		}
		if(tmp==null) return;

		tmp.setVal(v);
	}

	public void reverse(){
		Node tmp=head;
		Node tmp2=null;
		while(tmp!=null){
			tmp2=tmp.getPrev();
			tmp.setPrev(tmp.getNext());
			tmp.setNext(tmp2);
			tmp=tmp.getPrev();
		}
		head=tmp2.getPrev();
	}

	public String toString(){
		Node tmp=head;
		String s="";
		while(tmp.getNext()!=null){
			s+=tmp+",";
			tmp=tmp.getNext();
		}
		s+=tmp;
		return s;
	}
}