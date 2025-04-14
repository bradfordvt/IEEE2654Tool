import sys
print("sys.path = ", sys.path)
import calculator

def main(argv):
    print("Entering main")
    ret = calculator.press_button("TestTop.EXPR.RPN.B9") 
    print("ret(1) = ", ret)
    ret = calculator.press_button("TestTop.EXPR.RPN.B0") 
    print("ret(2) = ", ret)
    ret = calculator.press_button("TestTop.EXPR.RPN.BENTER") 
    print("ret(3) = ", ret)
    ret = calculator.press_button("TestTop.EXPR.RPN.B1") 
    print("ret(4) = ", ret)
    ret = calculator.press_button("TestTop.EXPR.RPN.B0") 
    print("ret(5) = ", ret)
    ret = calculator.press_button("TestTop.EXPR.RPN.BENTER") 
    print("ret(5a) = ", ret)
    ret = calculator.press_button("TestTop.EXPR.RPN.BPLUS") 
    print("ret(6) = ", ret)
    ret = calculator.read_display("TestTop.EXPR.RPN.DISPLAY") 
    print("ret(7) = ", ret)
    ret = calculator.show_display("TestTop.EXPR.RPN.DISPLAY") 
    print("ret(8) = ", ret)
    return 0;

if __name__ == "__main__":
    print("Entering __main__")
    sys.exit(main(sys.argv))
