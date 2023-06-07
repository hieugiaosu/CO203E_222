class Basic_class{
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
}
public class Derive_basic_class extends Basic_class {
    private int derive_atribute;
    Derive_basic_class(int for_private, double for_protected, int derive_atribute){
        super(for_private,for_protected);
        this.derive_atribute = derive_atribute;
        System.out.println("This is Derive_basic_class");
        System.out.println("This derive_atribute value: "+this.derive_atribute);
    }
    Derive_basic_class(){
        this(0,0,0);
    }
    @Override
    public void say_hello() {
        System.out.println("bonjour");
    }
    public static void main(String[] args) {
        Derive_basic_class derive_basic_class = new Derive_basic_class();
        derive_basic_class.say_hello();
    }
}
