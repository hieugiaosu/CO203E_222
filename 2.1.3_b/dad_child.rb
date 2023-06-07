class Dad
    attr_accessor :name 
    def initialize(name)
        @name = name
    end
    def greeting
        puts "Hello, my name is #{@name}."
    end
    def hair_color
        puts "My hair color is red"
    end
end

class Child < Dad
    def hair_color
        puts "My hair color is blue"
    end
end

alex = Child.new("Alex")
alex.greeting #Hello, my name is Alex
alex.hair_color #My hair color is blue