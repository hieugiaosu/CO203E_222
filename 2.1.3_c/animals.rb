class Animal
  def speak
    raise NotImplementedError, "This is abstract class."
  end
end

class Dog < Animal
  def speak
    puts "Gau gau!"
  end
end

class Cat < Animal
  def speak
    puts "Meo meo!"
  end
end

dog = Dog.new
dog.speak # "Gau gau!"

cat = Cat.new
cat.speak # "Meo meo!"
