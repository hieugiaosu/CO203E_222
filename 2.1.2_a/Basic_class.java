public class Basic_class{
    private int private_atribute;
    protected double protected_atribute;
    public Basic_class(int for_private, double for_protected){
        this.private_atribute = for_private;
        this.protected_atribute = for_protected;
        System.out.println("This is basic_class");
        System.out.println("private_atribute value: " + this.private_atribute);
        System.out.println("this protected_atribute value: " + this.protected_atribute);
    }
    public void say_hello() {
        System.out.println("Hello World");
    }
    public Basic_class(){
        this(0,0);
    }
    public static void main(String[] args) {
        Basic_class basic_class1 = new Basic_class(14, 2.0);
        Basic_class basic_class2 = new Basic_class();
        basic_class1.say_hello();
        basic_class2.say_hello();
    }
}
