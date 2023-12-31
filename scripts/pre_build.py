import sys
import shutil
from utils import *

type = sys.argv[1]

# append "#pragma once" to all header files if not already present
for f in dir("src"):
  if f.endswith(".h"):
    s = read(f"src/{f}")
    if not s.startswith("#pragma once"):
      s = "#pragma once\n" + s
      write(f"src/{f}", s)

shutil.rmtree(f"build/{type}/models", ignore_errors=True)
shutil.rmtree(f"build/{type}/shaders", ignore_errors=True)
shutil.rmtree(f"build/{type}/textures", ignore_errors=True)