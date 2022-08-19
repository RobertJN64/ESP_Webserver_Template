import os

files = os.listdir("html")

with open("include/html.hpp", "w+") as f:
    f.write("#include <Arduino.h>\n")

    for item in files:
        if item.endswith(".html") or item.endswith(".css") or item.endswith(".js"):
            print("Moving contents of file:", item)
            fname = item.replace(" ", "_").replace(".", "_")
            f.write('\nconst char ' + fname + '[] PROGMEM = R"rawliteral(\n')
            with open("html/" + item) as f2:
                f.write(f2.read())
            f.write('\n)rawliteral";\n')