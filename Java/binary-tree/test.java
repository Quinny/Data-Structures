public class test{
	public static void main(String[]args){
		new Node();

		BTree<Integer> tree=new BTree<Integer>();

		tree.add(5);
		tree.add(4);
		tree.add(17);
		tree.add(18);

		tree.displayPre();

		System.out.println(tree.maxNodesPerRow());
	}
}