import os

# append "#pragma once" to all header files if not already present
for file in os.listdir("src"):
  if file.endswith(".h"):
    file_string = open(os.path.join("src", file), "r").read()
    if not file_string.startswith("#pragma once"):
      file_string = "#pragma once\n" + file_string
      open(os.path.join("src", file), "w").write(file_string)