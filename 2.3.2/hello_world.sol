pragma solidity >=0.4.22 <0.7.0;

contract Hello_World {
 
    string private message;
    
    function contructor(string memory mes) public {
        message = mes;
    }
    
    function setMessage(string memory mes) public {
        message = mes;
    }
    
    function getMessage() view public returns(string memory) {
        return message;
    }
}