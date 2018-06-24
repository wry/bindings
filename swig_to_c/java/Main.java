// run : java -cp obj -Djava.library.path=./obj/ Main

public class Main
{
	static
	{
		System.loadLibrary("hellob");
	}

	public static void main(String[] args)
	{
		System.out.println(hellob.hello(42));
	}
}

