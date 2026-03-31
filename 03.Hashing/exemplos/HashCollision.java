public class HashCollision
{
    public static void main(String args[])
    {
        // Colisoes
        String str1 = "Aa";
        String str2 = "BB";
        String str3 = "AaAaAaAa";
        String str4 = "AaAaAaBB";
        System.out.println(str1+": "+str1.hashCode());
        System.out.println(str2+": "+str2.hashCode());
        System.out.println(str3+": "+str3.hashCode());
        System.out.println(str4+": "+str4.hashCode());

    }

}

