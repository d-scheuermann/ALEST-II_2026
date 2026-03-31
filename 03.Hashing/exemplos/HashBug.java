public class HashBug
{
    public static void main(String args[])
    {
        // Demonstra como o hashCode pode FALHAR com determinadas
        // strings...
        //
        String str5 = "polygenelubricants";
        System.out.println(str5.hashCode());
        System.out.println(Math.abs(str5.hashCode()));
        System.out.println(str5.hashCode() & 0x7fffffff);
    }
}

