public class test{
	public static void main(String[]args){

		new Node(); //so that node gets compiled;

		LList<Integer>a=new LList<Integer>();
		a.add(5);
		a.add(6);
		a.add(7);
		a.add(8);
		System.out.println(a);
		a.remove(8);
		System.out.println(a);
		a.add(9);
		System.out.println(a);
		a.reverse();
		System.out.println(a);
		a.push(8);
		a.push(9);
		a.set(5,1);
		System.out.println(a);
	}
}