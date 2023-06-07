class Person
  attr_reader :name  # Phương thức getter
  attr_writer :age   # Phương thức setter
  protected

  def protected_method
    puts "This is a protected method"
  end
  private

  def private_method
    puts "This is a private method"
  end
end

person = Person.new