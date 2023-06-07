abstract class Animals{
    abstract void ability();
}

class Bat extends Animals{
    @Override
    void ability() {
        System.out.println("I can fly");
    }
}

class Man extends Animals{
    @Override
    void ability() {
        System.out.println("I can do Assignment");
    }
}

public class Abstract_and_Polymorphism {
    public static void main(String[] args) {
        Animals[] lst = new Animals[2];
        lst[0] = new Man();
        lst[1] = new Bat();
        lst[0].ability();
        lst[1].ability();
    }
}
