public class Main {

    public static void main(String[] args)
    {
        Queue<Integer> test=new Queue<Integer>();
        for (int i=0;i<2*test.dump;i++)
            test.offer(i);

        //test.add(1);

        if (test.offer(1)==false)
            System.out.println("Test offer method!");
        for (int i=0;i<2*test.dump;i++)
        {
            System.out.printf("cur:%d next:%d\n",test.poll(),test.peek());
        }

        test.remove();


    }
}
