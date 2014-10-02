import java.lang.Math;
import java.util.LinkedList;
import java.util.Queue;


public class BTree<T extends Comparable<? super T>>{
	private Node root;
	final int PRE=1;
	final int IN=2;
	final int POST=3;
	public BTree(){
		root=null;
	}

	public void add(T v){
		if(root==null){
			root=new Node(v);
		}
		else{
			add(new Node(v),root);
		}
	}

	public void add(Node n,Node branch){
		if(n.val().compareTo(branch.val())>0){
			if(branch.right()==null){
				branch.setRight(n);
			}
			else{
				add(n,branch.right());
			}
		}
		else{
			if(branch.left()==null){
				branch.setLeft(n);
			}
			else{
				add(n,branch.left());
			}
		}
	}
	public int maxNodesPerRow(){
		return maxNodesPerRow(root);
	}
	public int maxNodesPerRow(Node branch){
		int currentRow=1; //nodes in the current row
		int nextRow=0; //nodes in the next row
		int maxRow=0; //max nodes per row
		Queue <Node> q = new LinkedList<Node>();
		q.add(branch);
		while (!q.isEmpty()){
			Node current=q.peek();
			q.remove();

			if(current.right()!=null){
				nextRow++;
				q.add(current.right());
			}
			if(current.left()!=null){
				nextRow++;
				q.add(current.left());
			}

			if(currentRow==1){
				if(nextRow>maxRow){
					maxRow=nextRow;
				}
				currentRow=nextRow;
				nextRow=0;
			}
			else{
				currentRow--;
			}
		}
		return maxRow;
	}
	public int maxDepth(){
		return maxDepth(root);
	}
	public int maxDepth(Node branch){
		if(branch==null) return 0;

		return 1+Math.max(maxDepth(branch.right()),maxDepth(branch.left()));
	}

	public void displayIn(){
		display(root,IN);
	}
	public void displayPre(){
		display(root,PRE);
	}
	public void displayPost(){
		display(root,POST);
	}
	
	public void display(Node branch,int type){
		if(branch==null) return;
		if(type==PRE) System.out.println(branch.val());
		display(branch.left(),type);
		if(type==IN) System.out.println(branch.val());
		display(branch.right(),type);
		if(type==POST) System.out.println(branch.val());
	}
}