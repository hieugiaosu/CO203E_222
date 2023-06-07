interface Human {
    void talk();
}

interface Bat {
    void fly();
}

class Batman implements Human, Bat {
    public void talk() {
        System.out.println("I'm Batman");
    }

    public void fly() {
        System.out.println("Batman is flying");
    }
}

public class Interface_test {
    public static void main(String[] args) {
        Batman batman = new Batman();
        batman.talk(); // Output: I'm Batman
        batman.fly(); // Output:  Batman is flying
    }
}
