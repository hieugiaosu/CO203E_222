module Swimmable
  def swim
    puts "Swimming..."
  end
end

class Animal
  # ...
end

class Fish < Animal
  include Swimmable
end

class Mammal < Animal
  # ...
end

class Dolphin < Mammal
  include Swimmable
end

fish = Fish.new
fish.swim # "Swimming..."
dolphin = Dolphin.new
dolphin.swim # "Swimming..."
