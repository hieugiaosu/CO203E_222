class Person
  attr_accessor :name, :age

  def initialize(name, age)
    @name = name
    @age = age
  end

  def say_hello
    puts "Hello, my name is #{@name} and I am #{@age} years old."
  end
end
person = Person.new("TheHieu", 20)
puts person.name  # Output: TheHieu
puts person.age   # Output: 20
person.say_hello  # Output: Hello, my name is TheHieu and I am 20 years old.