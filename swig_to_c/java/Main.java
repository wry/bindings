public class Main
{
	static
	{
		System.loadLibrary("Lar");
	}

	public static void main(String[] args)
	{
        SWIGTYPE_p_Lar lar = Lar.Lar_new();

        // will crash if path incorrect, should pass a char**
        SWIGTYPE_p_p_char error = new SWIGTYPE_p_p_char();
        SWIGTYPE_p_Release release = Lar.Lar_first_release_item(lar, "/tmp/releases.rss", error);

        if (release == null)
        {
            System.err.println(String.format("Error : %s", error));
            // free(error);
            return;
        }

        CRelease crelease = new CRelease();
        Lar.Release_copy_into(release, crelease);

        System.out.println(String.format("%s, %s, %s, %s\n", crelease.getTitle(), crelease.getLink(), crelease.getDescription(), crelease.getPub_date()));

        Lar.Release_delete(release);
        
        Lar.Lar_delete(lar);
	}
}

