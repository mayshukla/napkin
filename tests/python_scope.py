# Testing how python scoping works for reference

x = 1

def do():
    global x
    def inner():
        global x
        while x < 10:
            x += 1
            print(x)
    inner()

do()
print(x)
