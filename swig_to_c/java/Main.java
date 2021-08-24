public class Main
{
	static
	{
		System.loadLibrary("Lar");
	}

	public static void main(String[] args)
	{
        SWIGTYPE_p_Lar lar = Lar.Lar_new();

        // will crash if path incorrect, should pass a char** (cstring.i not implemented for this target)
        Result result = Lar.Lar_first_release_item_ex(lar, "/tmp/releases.rss");

        if (result.getResult() == null)
        {
            System.err.println(String.format("Error : %s", result.getError()));
            // free(error);
            return;
        }

        CRelease crelease = new CRelease();
        Lar.Release_copy_into(result.getResult(), crelease);

        System.out.println(String.format("%s, %s, %s, %s\n", crelease.getTitle(), crelease.getLink(), crelease.getDescription(), crelease.getPub_date()));

        Lar.Release_delete(result.getResult());
        
        Lar.Lar_delete(lar);
	}
}

