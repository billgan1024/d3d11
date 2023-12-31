def read(f):
  with open(f, "r") as f:
    return f.read()

def write(f, s):
  with open(f, "w") as f:
    f.write(s)