print("Before import Imperative_KEYPAD_pb2")
import Imperative_KEYPAD_pb2
print("Before import Imperative_DISPLAY_pb2")
import Imperative_DISPLAY_pb2
print("Before import Command_BUTTON_pb2")
import Command_BUTTON_pb2
print("Before import IEEE2654_pb2")
import IEEE2654_pb2
print("Before import IEEE2654DSL")
import IEEE2654DSL

button_response_flag = False
button_response_error = False

print("Before def button_response_handler")
def button_response_handler(target_:str, len_:int, message_:str) -> int:
    global button_response_flag
    global button_response_error
    print("Entering button_response_handler(", target_, ", ", len_, ")")
    button_response_flag = True
    print("message = ", message_)
    wrapper = IEEE2654_pb2.IEEE2654Message()
    wrapper.ParseFromString(message_)
    print("wrapper.metaname = ", wrapper.metaname)
    if wrapper.metaname == "IEEE2654ERROR":
        button_response_error = True
        errmsg = IEEE2654_pb2.IEEE2654Error()
        errmsg.ParseFromString(wrapper.setialized)
        print(errmsg.message)
        return -1
    else:
        if wrapper.metaname == "BUTTON":
            button_response_error = False
            return 0
        else:
            button_response_error = True
            return -4


print("Before def press_button")
def press_button(target_: str) -> int:
    global button_response_flag
    global button_response_error
    print("Entering press_button(", target_, ")")
    button = Imperative_KEYPAD_pb2.BUTTON();
    button.uid = 0
    button.function = "PRESS"
    wrapper = IEEE2654_pb2.IEEE2654Message()
    wrapper.UID = 0
    wrapper.metaname = "BUTTON"
    wrapper.serialized = button.SerializeToString()
    message = wrapper.SerializeToString()
    button_response_flag = False
    IEEE2654DSL.set_response_callback(button_response_handler)
    print("IEEE2654DSL.send_command_request(", target_, ", ", message, ")")
    ret = IEEE2654DSL.send_command_request(target_, len(message), message)
    print("Returned from IEEEDSL.send_command_request() with ret = ", ret)
    if ret:
        print("Failed to send request")
        return -1
    else:
        if button_response_flag == False:
            print("Failed to get a response")
            return -2
        elif button_response_error == True:
            print("An error was detected for button")
            return -3
        else:
            return 0

show_display_response_flag = False
show_display_response_error = False
show_display_value = 0

def display_show_response_handler(target_:str, len_:int, message_:str) -> int:
    global show_display_response_flag
    global show_display_response_error
    global show_display_value
    print("Entering display_show_response_handler(", target_, ", ", len_, ")")
    print("message_ = ", message_)
    show_display_response_flag = True
    wrapper = IEEE2654_pb2.IEEE2654Message()
    wrapper.ParseFromString(message_)
    if wrapper.metaname == "IEEE2654Error":
        show_display_response_error = True
        errmsg = IEEE2654_pb2.IEEE2654Error()
        errmsg.ParseFromString(wrapper.serialized)
        print(errmsg.message)
        return -1
    else:
        if wrapper.metaname == "DISPLAY":
            show_display_response_error = False
            display = Imperative_DISPLAY_pb2.DISPLAY();
            display.ParseFromString(wrapper.serialized)
            if display.function == "SHOW":
                show_display_value = display.value
                return 0
            else:
                display_response_error = True
                return -5
        else:
            display_response_error = True
            return -4


def show_display(target_: str) -> int:
    global show_display_response_flag
    global show_display_response_error
    global show_display_value
    print("Entering show_display(", target_, ")")
    display = Imperative_DISPLAY_pb2.DISPLAY();
    display.function = "SHOW"
    display.uid = 0
    display.value = "0"
    wrapper = IEEE2654_pb2.IEEE2654Message()
    wrapper.UID = 0
    wrapper.metaname = "DISPLAY"
    wrapper.serialized = display.SerializeToString()
    message = wrapper.SerializeToString()
    show_display_response_flag = False
    IEEE2654DSL.set_response_callback(display_show_response_handler)
    ret = IEEE2654DSL.send_command_request(target_, len(message), message)
    if ret:
        print("Failed to send request")
        return -1
    else:
        if show_display_response_flag == False:
            print("Failed to get a response")
            return -2
        elif show_display_response_error == True:
            print("An error was detected for display")
            return -3
        else:
            print(target_, " value = ", show_display_value)
            return 0

read_display_response_flag = False
read_display_response_error = False

def display_read_response_handler(target_:str, len_:int, message_:str) -> int:
    global read_display_response_flag
    global read_display_response_error
    print("Entering display_read_response_handler(", target_, ", ", len_, ")")
    print("message_ = ", message_)
    read_display_response_flag = True
    wrapper = IEEE2654_pb2.IEEE2654Message()
    wrapper.ParseFromString(message_)
    if wrapper.metaname == "IEEE2654Error":
        read_display_response_error = True
        errmsg = IEEE2654_pb2.IEEE2654Error()
        errmsg.ParseFromString(wrapper.serialized)
        print(errmsg.message)
        return -1
    else:
        if wrapper.metaname == "DISPLAY":
            display = Imperative_DISPLAY_pb2.DISPLAY();
            display.ParseFromString(wrapper.serialized)
            if display.function == "READ":
                read_display_response_error = False
                show_display_value = display.value
                return 0
            else:
                return -2
        else:
            display_response_error = True
            return -4


def read_display(target_: str) -> int:
    global read_display_response_flag
    global read_display_response_error
    print("Entering read_display(", target_, ")")
    display = Imperative_DISPLAY_pb2.DISPLAY();
    display.function = "READ"
    display.uid = 0
    display.value = "0"
    wrapper = IEEE2654_pb2.IEEE2654Message()
    wrapper.UID = 0
    wrapper.metaname = "DISPLAY"
    wrapper.serialized = display.SerializeToString()
    message = wrapper.SerializeToString()
    print("read_display: message = ", message)
    read_display_response_flag = False
    IEEE2654DSL.set_response_callback(display_read_response_handler)
    ret = IEEE2654DSL.send_command_request(target_, len(message), message)
    if ret:
        print("Failed to send request (ret = ", ret, ")")
        return -1
    else:
        if read_display_response_flag == False:
            print("Failed to get a response")
            return -2
        elif read_display_response_error == True:
            print("An error was detected for display")
            return -3
        else:
            return 0

