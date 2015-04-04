public class test{
	public static void main(String[]args){
		new Node();
		Stack<Integer>s=new Stack<Integer>();

		s.push(7);
		s.push(8);
		System.out.println(s.peek());
		s.pop();
		System.out.println(s.peek());
		s.pop();
		System.out.println(s.isEmpty());
		s.push(9);
		System.out.println(s.isEmpty());
	}
}