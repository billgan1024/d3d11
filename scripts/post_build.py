import os
import re
import sys
import shutil
from utils import *

type = sys.argv[1]

# replace fbx with gltf
for f in os.listdir("models"):
  if f.endswith(".fbx"):
    os.system(f"fbx2gltf models/{f} -e -o models/{f[:-4]}.gltf")
    os.remove(f"models/{f}")

shutil.copytree("models", f"build/{type}/models")
shutil.copytree("textures", f"build/{type}/textures")

sm = "5_0"

os.mkdir(f"build/{type}/shaders")
# for each shader entry point among hlsl files, compile it
for f in os.listdir(f"shaders"):
  if f.endswith(".hlsl"):
    s = read(f"shaders/{f}")
    for main in re.compile("[A-Za-z0-9_]+_[vpcg]s").findall(s):
      print(main)
      cmd = f"fxc shaders/{f} -T {main[-2:]}_{sm} -E {main} -Fo build/{type}/shaders/{main}.cso"
      if type == "Debug":
        cmd += " -Zi -Od"

      cmd += f" -Fc build/{type}/shaders/{main}.asm"
      os.system(cmd)
